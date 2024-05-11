// Gestione output su Nextion
void sendNextionCommand(const char* command){
  nexSerial.print(command);
  nexSerial.write(0xFF);
  nexSerial.write(0xFF);
  nexSerial.write(0xFF);
}
void updateSCR_nex(){
  char comando[100];
  comando[0] = '\0';
  strcpy(comando, "g0.txt=\"");
  const char *nomeradio;
  record = radioRecords[STATION].as<JsonObject>();
  if(record.containsKey(POS3)){
    nomeradio = record[POS3];
  }
  strcat(comando, nomeradio);
  strcat(comando,"\"");
  sendNextionCommand(comando);
  // Invio numero stazione a Nextion
  char append[3];
  append[0] = '\0';
  comando[0] = '\0';
  strcpy(comando, "n0.val=");
  sprintf(append,"%d", STATION);
  strcat(comando, append);
  sendNextionCommand(comando);
  // Invio volume a Nextion
  append[0] = '\0';
  comando[0] = '\0';
  strcpy(comando, "j0.val=");
  sprintf(append,"%d", VOLUME);
  strcat(comando, append);
  sendNextionCommand(comando);
  // Invio data ora a Nextion
  comando[0] = '\0';
  strcpy(comando, "t0.txt=\"");
  strcat(comando, Data.c_str());
  strcat(comando, " - ");
  strcat(comando, Ora.c_str());
  strcat(comando, "\"");
  sendNextionCommand(comando);
  // Invio SSID e IP
  comando[0] = '\0';
  IPAddress LocalIP = WiFi.localIP();
  strcpy(comando, "g1.txt=\"SSID: ");
  strcat(comando, WiFi.SSID().c_str());
  strcat(comando, " - ");
  strcat(comando, "IP: ");
  for (int i=0; i<3; i++){
    append[0] = '\0';
    sprintf(append, "%d", LocalIP[i]);
    strcat(comando, append);
    strcat(comando, ".");
  }
  append[0] = '\0';
  sprintf(append, "%d", LocalIP[3]);
  strcat(comando, append);
  strcat(comando, " - ");
  strcat(comando, "Segnale: ");
  append[0] = '\0';
  sprintf(append, "%d", WiFi.RSSI());
  strcat(comando, append);
  strcat(comando, "\"");
  sendNextionCommand(comando);
}
void updateTimeScr_nex(){
  char comando[100];
  comando[0] = '\0';
  strcpy(comando, "g0.txt=\"");
  strcat(comando, Data.c_str());
  strcat(comando, " - ");
  strcat(comando, Ora.c_str());
  strcat(comando, "\"");
  sendNextionCommand(comando);
  // Invio numero stazione a Nextion
  char append[3];
  append[0] = '\0';
  comando[0] = '\0';
  strcpy(comando, "n0.val=");
  sprintf(append,"%d", STATION);
  strcat(comando, append);
  sendNextionCommand(comando);
  // Invio volume stazione a Nextion
  append[0] = '\0';
  comando[0] = '\0';
  strcpy(comando, "j0.val=");
  sprintf(append,"%d", VOLUME);
  strcat(comando, append);
  sendNextionCommand(comando);
  // Invio data ora a Nextion
  comando[0] = '\0';
  strcpy(comando, "t0.txt=\"OROLOGIO\"");
  sendNextionCommand(comando);
   
}
/*
void updateAPSCR_nex(unsigned int utimeout){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(2);
    display.println("AP Mode");
    display.setTextSize(1);
    display.print("AP: ");
    display.println((String)APEsp32);
    display.println("IP: 192.168.4.1");
    display.print("Timeout: ");
    display.print(utimeout);
    display.print("sec");
    display.display();
}


void printSCR_notavail_nex(){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Canale non disponibile...");
    //lcd.setCursor(0, 1);
    display.print("Riconnessione...");
    display.display();
    //delay(1000);
}

void printSCR_yesnet_nex(){
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Internet OK");
        display.print("SSID: ");
        display.println(WiFi.SSID());
        display.print("IP: ");
        display.println(WiFi.localIP());
        display.display();
}
void printSCR_nonet_nex(){
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("No Internet");
        display.display();
}
void printSCR_attesaWL_nex(){
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Attesa WIFI!");
        //lcd.setCursor(0, 1);
        display.print("Connessione...");
        display.display();
}
*/