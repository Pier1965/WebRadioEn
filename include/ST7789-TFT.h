void initSCR() {
  DEBUG_PRINTLN("Inizializzo TFT ST7789");
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display->begin()) {
    DEBUG_PRINTLN(F("ST7789 allocation failed... System locked"));
    for(;;); // Don't proceed, loop forever
  }
  #ifdef TFT_BL
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);
  #endif
  display->setRotation(1);
  display->fillScreen(BLACK);
  display->setTextSize(1);
  display->setTextColor(YELLOW);
  display->setCursor(0, 0);
  // Display static text
  display->println("WR PPPC65");
  display->println(Autore);
  display->println(eMailAutore);
  display->println(buildFor);
   //display.setCursor(0, 1);
  display->print(RelDate);
  //display->display();
  delay(1000);
}
void updateAPSCR(unsigned int utimeout){
    display->fillScreen(BLACK);
    display->setCursor(0, 0);
    display->setTextSize(2);
    display->println("AP Mode");
    display->setTextSize(1);
    display->print("AP: ");
    display->println((String)APEsp32);
    display->println("IP: 192.168.4.1");
    display->print("Timeout: ");
    display->print(utimeout);
    display->print("sec");
    //display->display();
}
void updateSCR(){
  const char *nomeradio;
  uint8_t fontSize = 1;
  int16_t x1, y1;
  uint16_t w, h;
  display->setCursor(0, 0);
  display->setFont(&FreeSans12pt7b);
  display->setTextSize(1);
  record = radioRecords[STATION].as<JsonObject>();
    if(record.containsKey(POS3)){
      nomeradio = record[POS3];
    }
  display->fillScreen(BLACK);
  display->setTextColor(YELLOW);
  display->getTextBounds(nomeradio, 0, 0, &x1, &y1, &w, &h); //calc width of new string
  display->setCursor(0, h);
  display->setTextSize(1);
  display->println(nomeradio);
  display->print("Vol: ");
  display->print(VOLUME);
  display->print("% ");
  display->setTextColor(RED);
  for(int i=0;i<10;i++){
    if(i>VOLUME/10)
      display->setTextColor(YELLOW);
    display->print("O");
  }
  display->println("");
  display->setTextColor(YELLOW);
  display->print("Stazione: ");
  display->println(STATION);
  display->setTextColor(RGB565_BLUE);
  display->print("SSID: ");
  display->println(WiFi.SSID());
  display->print("IP: ");
  display->println(WiFi.localIP());
  display->print("Segnale: ");
  display->println(WiFi.RSSI());
  //display.println("");
  display->setTextColor(GREEN);
  display->print(Data);
  display->print(" ");
  display->println(Ora);
  display->setTextColor(ORANGE);
  display->print(buildFor);
  display->setTextColor(YELLOW);
  display->setCursor(210, 150);
  display->setTextSize(3);
  display->print(STATION);
  //String myString = String(STATION);
  //display->getTextBounds(myString, 0, 0, &x1, &y1, &w, &h); //calc width of new string
  //display->drawRect(210, 150 - h, w, h, RED);
  display->setFont();
}
void updateTimeScr(){
    uint8_t fontSize = 1;
    display->setFont(&FreeSans12pt7b);
    display->fillScreen(BLACK);
    display->setTextColor(YELLOW);
    //display->setCursor(0, 0);
    //display->setTextSize(4); // carattere STD alto 7 pixel ursorSize 2 -> 14 pixel
    //display->println("");
    int16_t x1, y1;
    uint16_t w, h;
    display->setTextSize(2* fontSize);
    display->getTextBounds(Data, 0, 0, &x1, &y1, &w, &h); //calc width of new string
    display->setCursor(SCREEN_WIDTH /2 - w / 2, h+2);
    display->println(Data);
    display->setTextColor(GREEN);
    display->setTextSize(3*fontSize);
    display->getTextBounds(Ora, 0, 0, &x1, &y1, &w, &h);
    display->setCursor(SCREEN_WIDTH / 2 - w / 2, 4*(h + 2));
    display->println(Ora);
    display->setTextColor(RED);
    display->setTextSize(fontSize);
    display->getTextBounds(buildFor, 0, 0, &x1, &y1, &w, &h);
    display->setCursor(SCREEN_WIDTH / 2 - w / 2, SCREEN_HEIGHT/2 + fontSize /2);
    display->println(buildFor);
    //display->display();
}
void printSCR_notavail(){
    display->fillScreen(BLACK);
    display->setCursor(0, 0);
    display->println("Canale non disponibile...");
    //lcd.setCursor(0, 1);
    display->print("Riconnessione...");
    //display->display();
    //delay(1000);
}

void printSCR_yesnet(){
        display->fillScreen(BLACK);
        display->setCursor(0, 0);
        display->println("Internet OK");
        display->print("SSID: ");
        display->println(WiFi.SSID());
        display->print("IP: ");
        display->println(WiFi.localIP());
        //display->display();
}
void printSCR_nonet(){
        display->fillScreen(BLACK);
        display->setCursor(0, 0);
        display->print("No Internet");
        //display->display();
}
void printSCR_attesaWL(){
        display->fillScreen(BLACK);
        display->setCursor(0, 0);
        display->println("Attesa WIFI!");
        //lcd.setCursor(0, 1);
        display->print("Connessione...");
        //display->display();
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