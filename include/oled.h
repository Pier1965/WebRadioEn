void initSCR() {
  DEBUG_PRINTLN("Inizializzo OLED");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    DEBUG_PRINTLN(F("SSD1306 allocation failed... System locked"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // Display static text
  display.println("WR PPPC65");
   //display.setCursor(0, 1);
  display.print(RelDate);
  display.display();
  delay(1000);
}
void updateAPSCR(unsigned int utimeout){
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
void updateSCR(){
  const char *nomeradio;
    record = radioRecords[STATION].as<JsonObject>();
      if(record.containsKey(POS3)){
        nomeradio = record[POS3];
      }
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println(nomeradio);
    display.print("Vol: ");
    display.print(VOLUME);
    display.println("%");
    display.print("Stazione: ");
    display.println(STATION);
    display.print("SSID: ");
    display.println(WiFi.SSID());
    display.print("IP: ");
    display.println(WiFi.localIP());
    display.print("Segnale: ");
    display.println(WiFi.RSSI());
    //display.println("");
    display.println(Data);
    display.println(Ora);
    display.display();
}
void updateTimeScr(){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.setTextSize(1);
    display.println("");
    int16_t x1, y1;
    uint16_t w, h;
    display.setTextSize(2);
    display.getTextBounds(Data, 0, 0, &x1, &y1, &w, &h); //calc width of new string
    display.setCursor(64 - w / 2, 2);
    display.println(Data);
    display.setTextSize(4);
    display.getTextBounds(Ora, 0, 0, &x1, &y1, &w, &h);
    display.setCursor(64 - w / 2, 32);
    display.println(Ora);
    display.display();
}
void printSCR_notavail(){
    display.clearDisplay();
    display.setCursor(0, 0);
    display.println("Canale non disponibile...");
    //lcd.setCursor(0, 1);
    display.print("Riconnessione...");
    display.display();
    //delay(1000);
}

void printSCR_yesnet(){
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Internet OK");
        display.print("SSID: ");
        display.println(WiFi.SSID());
        display.print("IP: ");
        display.println(WiFi.localIP());
        display.display();
}
void printSCR_nonet(){
        display.clearDisplay();
        display.setCursor(0, 0);
        display.print("No Internet");
        display.display();
}
void printSCR_attesaWL(){
        display.clearDisplay();
        display.setCursor(0, 0);
        display.println("Attesa WIFI!");
        //lcd.setCursor(0, 1);
        display.print("Connessione...");
        display.display();
}
/*
void printSCR_ChVolStn (){
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(1);
  display.println("");
  int16_t x1, y1;
  uint16_t w, h;
  display.setTextSize(2);
  display.getTextBounds((String)VOLUME, 0, 0, &x1, &y1, &w, &h); //calc width of new string
  display.setCursor(64 - w / 2, 8);
  display.println(VOLUME);
  //display.setTextSize(4);
  //display.getTextBounds(Ora, 0, 0, &x1, &y1, &w, &h);
  //display.setCursor(64 - w / 2, 36);
  //display.println(Ora);
  display.display();
}
*/