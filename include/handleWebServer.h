void webSocketEvent(byte num, WStype_t type, uint8_t * payload, size_t length){
  switch (type) {
  case WStype_DISCONNECTED:
    DEBUG_PRINTLN("Client disconnected");
    webSocket.close();
    delay(100);
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    break;
  case WStype_CONNECTED:
    DEBUG_PRINTLN("Client connected");
    break;
  case WStype_TEXT:
    DeserializationError error = deserializeJson(jsonDoc_rx, payload);
    if(error){
      DEBUG_PRINTLN("Deserialization jsonDoc_rx failed");
      return;
    } else {
      DEBUG_PRINTLN("Gestione pacchetto jsonDoc_rx ricevuto da client");
      int msg_pos1  = jsonDoc_rx["pos1"];
      int msg_pos2  = jsonDoc_rx["pos2"];
      const char* msg_url = jsonDoc_rx["url"];
      const char* msg_cmd = jsonDoc_rx["cmd"];
      const char* msg_nome = jsonDoc_rx["nome"];
      const char* msg_gene = jsonDoc_rx["gene"];
      DEBUG_PRINTLN("-------------------------");
      DEBUG_PRINTLN("Pos1: " + String(msg_pos1));
      DEBUG_PRINTLN("Pos2: " + String(msg_pos2));
      DEBUG_PRINTLN("Url: " + String(msg_url));
      DEBUG_PRINTLN("Comando: " + String(msg_cmd));
      DEBUG_PRINTLN("Nome: " + String(msg_nome));
      DEBUG_PRINTLN("Genere: " + String(msg_gene));
      DEBUG_PRINTLN("-------------------------");
      String s_msg_cmd = (String) msg_cmd;
      if(s_msg_cmd == "play"){
        DEBUG_PRINTLN("Comando play");
        if(abs(msg_pos1) < NR)
          STATION = abs(msg_pos1);
        return;
      }
      if(s_msg_cmd == "vol"){
        DEBUG_PRINTLN("Comando vol");
        msg_pos1 = abs(msg_pos1);
        if(msg_pos1 <= 100)
          VOLUME = msg_pos1;
        else
          VOLUME = 100;
        return;
      }
      if(s_msg_cmd == "add"){
        DEBUG_PRINTLN("Comando add");
        DEBUG_PRINTLN(msg_url);
        DEBUG_PRINT("Ora ci sono ");
        DEBUG_PRINTDEC(NR);
        DEBUG_PRINTLN(" stazioni");
        //    
        addRadio( radioRecords, 
            msg_pos1,
            msg_url,
            msg_nome, 
            msg_gene
        );
        if(!updateFileRadio()){
            radioRecords.remove(NR);
        }
        return;
      }
      if(s_msg_cmd == "del"){
        DEBUG_PRINTLN("Comando del");
        delRadio(radioRecords, msg_pos1);
        if(!updateFileRadio()){
            DEBUG_PRINTLN("Impossibile cancellare lo stream");
        }
        return;
      }
      if(s_msg_cmd == "delP1P2"){
        DEBUG_PRINTLN("Comando del da P1 a P2");
        for(int i = 0; i < (msg_pos2-msg_pos1+1); i++)
          delRadio(radioRecords, msg_pos1);
        if(!updateFileRadio()){
            DEBUG_PRINTLN("Impossibile cancellare gli stream");
        }
        return;
      }
      if(s_msg_cmd == "move"){
        DEBUG_PRINTLN("Comando move");
        DEBUG_PRINT("Spostare Pos1: ");
        DEBUG_PRINTDEC(msg_pos1);
        DEBUG_PRINT(" alla Pos2: ");
        DEBUG_PRINTDEC(msg_pos2);
        DEBUG_PRINTLN();
        moveRadio(radioRecords, msg_pos1, msg_pos2);
        if(!updateFileRadio()){
            DEBUG_PRINTLN("Impossibile spostare lo stream");
        }
          return;
      }
      if(s_msg_cmd == "swap"){
        DEBUG_PRINTLN("Comando swap");
        DEBUG_PRINT("Scambiare Pos1: ");
        DEBUG_PRINTDEC(msg_pos1);
        DEBUG_PRINT(" con Pos2: ");
        DEBUG_PRINTDEC(msg_pos2);
        DEBUG_PRINTLN();
        swapRadio(radioRecords, msg_pos1, msg_pos2);
        if(!updateFileRadio()){
            DEBUG_PRINTLN("Impossibile scambiare gli stream");
        }
          return;
      }
      if(s_msg_cmd == "search"){
          DEBUG_PRINTLN("Comando search");
          return;
      }
      if(s_msg_cmd == "update"){
          DEBUG_PRINTLN("Comando update");
          webSocket.broadcastTXT(jsonString);
          return;
      }
      DEBUG_PRINTLN("Comando non previsto");
      DEBUG_PRINTLN(s_msg_cmd);
    }
    break;
  }
}
void handleFileUpload();
void handleRoot();
void startServer() {
    server.on("/", [](){
        server.send(200, "text/html", htmlContent);
    });
    //server.on("/", HTTP_GET, handleRoot);
    server.on("/upload", handleFileUpload);
    server.begin();
    delay(1000);
    DEBUG_PRINTLN("HTTP server started");
    webSocket.begin();
    webSocket.onEvent(webSocketEvent);
    jsonString = "";
    serializeJson(jsonDoc_tx, jsonString);
    DEBUG_PRINTLN("-------------- jsonString --------------------");
    DEBUG_PRINTLN(jsonString);
    DEBUG_PRINTLN("-------------- jsonString --------------------");
    delay(1000);
    webSocket.broadcastTXT(jsonString);
    DEBUG_PRINTLN("WebSocket server started");
}
void handleFileUpload() {
  File file;
  if(SPIFFS.exists("/cacca.txt")){
     SPIFFS.remove("/cacca.txt");
     DEBUG_PRINTLN("cacca.txt rimosso");
  }
  DEBUG_PRINTLN("Uploading...");
  HTTPUpload& upload = server.upload();
  String filename = "/cacca.txt";
  if (!filename.startsWith("/")) {
    filename = "/" + filename;
  }
  DEBUG_PRINT("handleFileUpload Name: "); DEBUG_PRINTLN(filename);
  file = SPIFFS.open(filename, "w");
  //filename = String();
  DEBUG_PRINT("handleFileUpload Data: "); DEBUG_PRINTLN(upload.currentSize);
  if (file) {
    file.write(upload.buf, upload.currentSize);
  } else {
    DEBUG_PRINTLN("Impossibile aprire il file cacca.txt in scrittura");
    return;
  }
  if (file) {
    file.close();
  }
  DEBUG_PRINT("handleFileUpload Size: "); DEBUG_PRINTLN(upload.totalSize);
  if(!SPIFFS.exists("/cacca.txt")){
    DEBUG_PRINTLN("cacca.txt non esiste");
    return;
  }
  file = SPIFFS.open("/cacca.txt", "r");
  unsigned int Size = file.size();
  DEBUG_PRINT("Dimensione del file cacca.txt: ");
  DEBUG_PRINTDEC(Size);
  DEBUG_PRINTLN("");
  String message = "Dimensione del file: ";
  String content = file.readString();
  file.close();
  message += Size;
  message += "\n";
  message += "Contenuto del file\n";
  message += content;
  DEBUG_PRINTLN(message);
  //server.send(200, "text/plain", message);
  DeserializationError error = deserializeJson(jsonDoc_tx, content);
  if (error) {
    DEBUG_PRINT("JSON parsing failed: ");
    DEBUG_PRINTLN(error.c_str());
    return;
  }
  if(!updateFileRadio()){
    DEBUG_PRINTLN("Impossibile aggiornare la lista radio con il file ricevuto");
  }
  if(SPIFFS.exists("/cacca.txt")){
     SPIFFS.remove("/cacca.txt");
     DEBUG_PRINTLN("cacca.txt rimosso");
  }
}
