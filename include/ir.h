//void setNumberStation(unsigned int digitSent);
void StartIR(){
    DEBUG_PRINTLN("Inizializzo sensore IR");
    irrecv.enableIRIn(); // Start the receiver
}
//------------------------------------------------------------------------------------
void checkIR(){
  // Tempo di ricevimento dei digit numerici
  const unsigned long irTimeWait = 1000;
  // 3 numero max digit inviati da pressione tasti su telecomando
  // 3 - 1 = 2 -> 99 max
  const unsigned char maxIrDigit = 3;
  // Canale stazione temporaneo prima scadenza tempo acquisizione
  static unsigned int TMP_STATION;
  // Bool vero se tempo scaduto e timer avviato da primo tasto 
  // per aggiornamento sola stazione
  static bool updateStation;
  // tempo di ricevimento del primo digit
  static unsigned long timerIrStartedAt = 0;
  // Tempo passato dall'arrivo del primo digit IR
  static unsigned long timeIrElapsed = 0;
  // switch che è true se si è ricevuto il primo digit
  static bool timerIrStarted = false;
  // tempo di ricevimento del digit
  unsigned long timeIrCodeArrived = 0;
  // Switch per decisione verifica codici comando vol stn o numeri
  static bool chkAlfa = false;
  static bool chkNmbr = false;
  // Switch sul primo digit ricevuto
  static bool firstDigit = false;
  // Numero di digit ricevuti nel tempo di "ascolto" dei pulsanti
  static unsigned char digitIrCount = 0;
  // Se il timer di accettazione dei tasti numerici è in funzione ma è scaduto
  // se ci sono caratteri numerici aggiorno stazione resetto tutto e torno
  if(timerIrStarted){
    timeIrElapsed = millis() - timerIrStartedAt;
    if(timeIrElapsed > irTimeWait){
      if(updateStation){
        updateStation = false;
        STATION = TMP_STATION % NR;
        TMP_STATION = 0;
        DEBUG_PRINT("Stazione: ");
        DEBUG_PRINTDEC(STATION);
        DEBUG_PRINTLN(" ");
        updateEeprom();
      }
      TMP_STATION = 0;
      timerIrStarted = false;
      chkAlfa = false;
      chkNmbr = false;
      firstDigit = false;
      timeIrElapsed = 0;
      digitIrCount = 0;
      timeIrCodeArrived = 0;
      timerIrStartedAt = 0;
      return;
    }
  }
  // Il timer accettazione tasti o non è ancora partito o non è scaduto
  // Inviato codice IR?
  if (irrecv.decode(&results)) {
    // Utile per testare i codici di un nuovo telecomando
    #ifdef SPION
      DEBUG_PRINTLN("Ir attivato...");
      DEBUG_PRINT("Codice IR: ");
      serialPrintUint64(results.value, HEX);
      DEBUG_PRINTLN("");
    #endif
    // Tempo di arrivo del codice IR
    timeIrCodeArrived = millis();
    if(!timerIrStarted){
      // Il timer non è ancora partito quindi è arrivato il primo carattere
      timerIrStarted = true;
      timerIrStartedAt = timeIrCodeArrived;
      firstDigit = true;
    } else {
      // Il timer era già partito ma non scaduto 
      firstDigit = false; 
    }
    //timeIrElapsed = timeIrCodeArrived - timerIrStartedAt;
    // E' il primo codice che arriva?
    if(firstDigit){ 
      // SI
      // Controllare sia i numeri che i comandi di volume e stz alla prima iterazione
      chkNmbr = true;
      chkAlfa = true;
    }else{ 
      // NO
      // Controllare solo i numeri che possono essere presenti come secondo o terzo carattere
      chkNmbr = true;
      chkAlfa = false;
    }
    // Controllo se arriva un comando cambio volume o stazione
    if(chkAlfa){
      // Controllo i comandi solo al primo digit
      chkAlfa = false;
      // Elaborazione dei codici NON numerici
      // Che cambiano immediatamente stazione e volume
      // e che funzionano una volta ogni irTimeWait
      switch (results.value) {
        case IR_UP: 
        #ifdef TANIX 
          case IR_UP_ALT: 
        #endif
        #ifdef ZODIAC
          case IR_UP1:
        #endif
          DEBUG_PRINTLN("Volume UP");
          if(VOLUME < (100 - DVOL))
            VOLUME += DVOL;
          else
            VOLUME = 100;
            // Se arriva un comando disabilito il successivo controllo dei numeri
          chkNmbr = false;
        break;
        case IR_DN:
        #ifdef TANIX
          case IR_DN_ALT:
        #endif
        #ifdef ZODIAC
          case IR_DN1:
        #endif
          DEBUG_PRINTLN("volume DOWN");
          if(VOLUME > DVOL)
            VOLUME -= DVOL;
          else
            VOLUME = 0;
          chkNmbr = false;
        break;
        case IR_NX:
        #ifdef ZODIAC
          case IR_NX1:
        #endif
          DEBUG_PRINTLN("Next");
          if(STATION<NR-1)
            STATION++;
          else
            STATION = 0;
          nxtButton = 1;
          prvButton = 0;
          chkNmbr = false;
        break;
        case IR_PV:
        #ifdef ZODIAC
          case IR_PV1:
        #endif
          DEBUG_PRINTLN("PREV");
            if(STATION>0)
              STATION--;
            else
              STATION = NR-1;
            nxtButton = 0;
            prvButton = 1;
            chkNmbr = false;
        break;
        #ifdef ZODIAC
          case IR_RS1:
            delay(1000);
            updateEeprom();
            WMode = !WMode;
            DEBUG_PRINTLN("Cambio modalità di funzionamento");
          break; 
        #endif
        case IR_RS:
          DEBUG_PRINTLN("Cambio modalità di funzionamento");
          delay(1000);
          updateEeprom();
          //ESP.restart(); Tasto di spegnimento del telecomando x reset
          WMode = !WMode;
        break;
        default:
          /*
          */
        break;
      }
      updateEeprom();
    }
    // Controllo se arriva un valore numerico per cambio stazione con tastierino numerico
    // per i telecomandi che lo prevedono
    if(chkNmbr){
      // Elaborazione dei codici numerici con i telecomandi forniti
      // di tastierino (CarMp3 funziona a cazzo di cane)
      // Funzionano solo nella finestra irTimeWait per un massino di 2 caratteri
      #if defined(ELEGO_IR) || defined(CARMP3) || defined(KC808) || defined(TANIX) || defined(ZODIAC)
      switch (results.value) {
        case IR_00:
        DEBUG_PRINTLN("IR_00");
        digitIrCount++;
        if(digitIrCount < maxIrDigit)
          TMP_STATION = TMP_STATION * 10 + 0;
        updateStation = true;
        break;
        case IR_01:
        DEBUG_PRINTLN("IR_01");
        digitIrCount++;
        if(digitIrCount < maxIrDigit)
          TMP_STATION = TMP_STATION * 10 + 1;
        updateStation = true;
        break;
        case IR_02:
        DEBUG_PRINTLN("IR_02");
        digitIrCount++;
        if(digitIrCount < maxIrDigit)
          TMP_STATION = TMP_STATION * 10 + 2;
        updateStation = true;
        break;
        case IR_03:
        DEBUG_PRINTLN("IR_03");
        digitIrCount++;
        if(digitIrCount < maxIrDigit)
          TMP_STATION = TMP_STATION * 10 + 3;
        updateStation = true;
        break;
        case IR_04:
        DEBUG_PRINTLN("IR_04");
        digitIrCount++;
        if(digitIrCount < maxIrDigit)
          TMP_STATION = TMP_STATION * 10 + 4;
        updateStation = true;
        break;
        case IR_05:
        DEBUG_PRINTLN("IR_05");
        digitIrCount++;
        if(digitIrCount < maxIrDigit)
          TMP_STATION = TMP_STATION * 10 + 5;
        updateStation = true;
        break;
        case IR_06:
        DEBUG_PRINTLN("IR_06");
        digitIrCount++;
        if(digitIrCount < maxIrDigit)
          TMP_STATION = TMP_STATION * 10 + 6;
        updateStation = true;
        break;
        case IR_07:
          DEBUG_PRINTLN("IR_07");
          digitIrCount++;
          if(digitIrCount < maxIrDigit)
            TMP_STATION = TMP_STATION * 10 + 7;
          updateStation = true;
        break;
        case IR_08:
          DEBUG_PRINTLN("IR_08");
          digitIrCount++;
          if(digitIrCount < maxIrDigit)
            TMP_STATION = TMP_STATION * 10 + 8;
          updateStation = true;
        break;
        case IR_09:
          DEBUG_PRINTLN("IR_09");
          digitIrCount++;
          if(digitIrCount < maxIrDigit)
            TMP_STATION = TMP_STATION * 10 + 9;
          updateStation = true;
        break;
        default:
        //
        break;
      }
      #endif
      DEBUG_PRINT("update station: ");
      DEBUG_PRINTDEC(updateStation);
      DEBUG_PRINTLN(" ");
      DEBUG_PRINT("TMP_STATION: ");
      DEBUG_PRINTDEC(TMP_STATION);
      DEBUG_PRINTLN(" ");
    }
    // Scarica il buffer e preparati a ricevere il prossimo
    irrecv.resume();
  }
}
//-----------------------------------------------------------------------------------
// Controllo del cambio stato clock <-> radio in modalità clock del solo tasto reset
bool checkReset(){
  // Inviato codice IR?
  if (irrecv.decode(&results)) {
    // Utile per testare i codici di un nuovo telecomando
    #ifdef SPION
      DEBUG_PRINTLN("Ir attivato...");
      DEBUG_PRINT("Codice IR: ");
      serialPrintUint64(results.value, HEX);
      DEBUG_PRINTLN("");
    #endif
    if(results.value==IR_RS) {
      WMode = !WMode;
      DEBUG_PRINTLN("Cambio modalità di funzionamento");
    }
    #ifdef ZODIAC
      if(results.value==IR_RS1) {
        WMode = !WMode;
        DEBUG_PRINTLN("Cambio modalità di funzionamento");
      }
    #endif
    irrecv.resume();
  }
  return(WMode);
}
