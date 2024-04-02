// Funzione che aggiunge un record di 4 campi all'array di records jsonRecord
// passato (array)  del jsonDoc_tx
void addRadio(JsonArray& array, unsigned char field1, const char* field2, const char* field3, const char* field4){
    if((field1 < 0) || (field1 > NR))
        field1 = NR;
    // Aggiungo un nuovo record in coda
    array.createNestedObject();
    // Conto il numero di record presenti
    uint8_t numeroRecords = array.size();
    // Copio i record dalla posizione in cui inserire il nuovo stream
    // di una posizione in alto e aggiorno il numero di posizione incrementandolo
    for(int i=numeroRecords-2; i>=field1; i--){
        array[i+1] = array[i];
        array[i+1][POS1]  = (unsigned char) (i+1);
        //JsonObject record = array[i+1];
        //record[POS1] = (unsigned char) (i+1);
    }
    // Sovrascrivo il nuovo stream nella posizione voluta
    array[field1][POS1] = field1;
    char buffer[100];
    sprintf(buffer, field2);
    array[field1][POS2] = buffer;
    buffer[0] = '\0';
    sprintf(buffer, field3);
    array[field1][POS3] = buffer;
    buffer[0] = '\0';
    sprintf(buffer, field4);
    array[field1][POS4] = buffer;
}
// Funzione che cancella il record di posizione field1 dall'array di records passato
void delRadio(JsonArray& array, const unsigned char field1){
    array.remove(field1);
    // Aggiorno gli indici delle radio successive
    NR = array.size();
    for(int i=field1; i<=NR-1; i++){
        array[i][POS1]  = (unsigned char) (i);
    }
}
// Funzione che sposta il record di posizione field1 alla posizione field2
void moveRadio(JsonArray& array, const unsigned char field1, const unsigned char field2){
    if(field1 == field2)
        return;
    // Aggiung il record di pos field1in posizione field2 aggiornando il 
    // numero di posizione a field2
    addRadio(radioRecords, field2, array[field1][POS2], array[field1][POS3], array[field1][POS4]);
    // Se lo spostamento è in su, l'aggiunta di un record non cambia la posizione dell'originale
    // da cancellare, altrimenti se lo spostamento è all'indietro, il vecchio record copiato, da cancellare,
    // si sposta in avanti di un posto a causa dell'aggiunta
    if(field2 > field1)
        delRadio(radioRecords, field1);
    else
        delRadio(radioRecords, field1+1);
    NR = array.size();
}
// Funzione che sposta il record di posizione field1 alla posizione field2
void swapRadio(JsonArray& array, const unsigned char field1, const unsigned char field2){
    if(field1 == field2)
        return;
    // Aggiungo un nuovo record in coda
    array.createNestedObject();
    NR = array.size();
    // Scambio i record
    array[NR-1] = array[field1];
    array[field1] = array[field2];
    array[field2] = array[NR-1];
    // Scambio i valori delle posizioni
    array[field1][POS1] = field1;
    array[field2][POS1] = field2;
    array.remove(NR-1);
    NR = array.size();
}
// Funzione di inizializzazione / recupero file lista radio e memorizzazione
// in un jsonDoc_tx per la memorizzazione delle radio e/o trasmissione al client
bool initRadioFileList(){
    #ifdef TESTRADIOFILE
        if(SPIFFS.remove(fileRadio)){
            DEBUG_PRINTLN("File radio rimosso in fase test");
        } else {
            DEBUG_PRINTLN("File radio non rimosso");
        }
    #endif
    // Se il file non esiste ne creo uno iniziale
    if(!SPIFFS.exists(fileRadio)){
        DEBUG_PRINTLN("File radio non inizializzato");
        File file = SPIFFS.open(fileRadio, FILE_WRITE);
        if(!file){
            DEBUG_PRINTLN("Impossibile creare file radio in scrittura");
            return false;
        } else {
            // Creo un file iniziale con 2 stazioni
            // Prima memorizzo i dati delle stazioni nella matrice
            // Json delle radio radioRecords che è un array
            // nel documento jsonDoc_tx
            addRadio(   radioRecords, 
                        0,
                        "http://icestreaming.rai.it/1.mp3",
                        "Rai Radio 1", 
                        "Generalista"
            );
            addRadio(   radioRecords, 
                        1,
                        "http://icestreaming.rai.it/2.mp3",
                        "Rai Radio 2", 
                        "Cagate"
            );
            addRadio(   radioRecords, 
                        2,
                        "http://icestreaming.rai.it/3.mp3",
                        "Rai Radio 3", 
                        "Cultura"
            );
            addRadio(   radioRecords, 
                        3,
                        "http://kraskp.ru:8000/mskregion",
                        "KP", 
                        "Informazione"
            );
            // e poi scrivo i dati della matrice Json radioRecords nel file
            // radio.txt
            if(serializeJson(jsonDoc_tx, file) == 0){
                DEBUG_PRINTLN("Impossibile scrivere il primo record");
                file.close ();
                return false;
            }
            file.close();
            // Numero di stazioni/record nell'array delle radio in jsonDoc_tx
            NR = radioRecords.size();
            DEBUG_PRINT("Aggiunte ");
            DEBUG_PRINTDEC(NR);
            DEBUG_PRINTLN(" radio");
            DEBUG_PRINTLN("Scritto il primo record: test di lettura...");
            #ifdef DEBUG
                File file = SPIFFS.open(fileRadio);
                if(!file){
                    DEBUG_PRINTLN("Impossibile aprire il file in lettura");
                    return false;
                }else{
                    DeserializationError error = deserializeJson(jsonDoc_tx, file);
                    if (error) {
                        Serial.print("deserializeJson() failed: ");
                        Serial.println(error.c_str());
                        return false;
                    }
                    for(JsonVariant element : jsonDoc_tx.as<JsonArray>()){
                        serializeJson(element, Serial);
                        Serial.println();
                    }
                    DEBUG_PRINTLN("");
                    file.close();
                    NR = radioRecords.size();
                    return true;
                }
            #endif
            return true;
        }
    }else{
        // apro in lettura il file esistente con l'elenco delle radio
        DEBUG_PRINTLN("File radio trovato");
        File file = SPIFFS.open(fileRadio, FILE_READ);
        if(!file){
            DEBUG_PRINTLN("Impossibile leggere file radio esistente");
            return false;
        }else{
            // metto il contenuto del file nell'array Json jsonDoc
            DeserializationError error = deserializeJson(jsonDoc_tx, file);
            if (error) {
                DEBUG_PRINT("DeserializeJson() di jsonDoc_tx failed: ");
                DEBUG_PRINTLN(error.c_str());
                return false;
            }
            file.close();
            DEBUG_PRINT("Lette ");
            NR = radioRecords.size();
            DEBUG_PRINTDEC(NR);
            DEBUG_PRINTLN(" radio");
            return true;
        }
    }
}
// Funzione che aggiorna il recode json delle radio e il file
bool updateFileRadio(){
    jsonString = "";
    serializeJson(jsonDoc_tx, jsonString);
    DEBUG_PRINTLN(jsonString);
    File file = SPIFFS.open(fileRadio, FILE_WRITE);
    if(serializeJson(jsonDoc_tx, file) == 0){
        DEBUG_PRINTLN("Impossibile aggiornare il file in updateFileRadio");
        file.close();
        return false;
    }
    NR = radioRecords.size();
    file.close();
    DEBUG_PRINT("Ora ci sono ");
    DEBUG_PRINTDEC(NR);
    DEBUG_PRINTLN(" stazioni");
    //serializeJson(jsonDoc_tx, jsonString);
    webSocket.broadcastTXT(jsonString);
    return true;
}
