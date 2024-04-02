bool wifi_connect(){
  WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP 
  WiFi.config(INADDR_NONE, INADDR_NONE, INADDR_NONE, INADDR_NONE);
  WiFi.setHostname(hostname.c_str()); //define hostname
  //
  WiFiManager wm;
  #ifdef TESTWIFI
    wm.resetSettings();
  #endif
  wm.setConfigPortalTimeout(TIMEOUT);
  bool res;
  res = wm.autoConnect(APEsp32); // password protected ap
  if(!res) {
    DEBUG_PRINTLN("Failed to connect");
    return(false);
  }
  else{
    WiFi.setSleep(false);
  }
  //if you get here you have connected to the WiFi
  DEBUG_PRINTLN("Connesso...");
  delay(2000); 
  return(true); 
}
/*
bool wifi_portal_chg(){
    // 
    WiFiManager wm; 
    // set configportal TIMEOUT
    wm.setConfigPortalTimeout(TIMEOUT);
    if (!wm.startConfigPortal(APEsp32)) {
      DEBUG_PRINTLN("failed to connect and hit TIMEOUT");
      //reset and try again, or maybe put it to deep sleep
      delay(5000);
      //ESP.restart();
      return(false);
    }  
    delay(500);
    //if you get here you have connected to the WiFi
    DEBUG_PRINTLN("Connesso...");  
    delay(2000);
    return(true);
}

void wifi_start(){
  if(!wifi_connect()){
      updateAPSCR(TIMEOUT);
      delay(2000);
      DEBUG_PRINTLN("Non Connesso...");  
      DEBUG_PRINTLN("ESP si riavvia...");
      ESP.restart();
  }
}
*/
/////////////
//Connessione con wifimanager
void setSsidPw(){
    // put your setup code here, to run once:
    DEBUG_PRINTLN("\n Starting AP");
    WiFi.mode(WIFI_STA); // explicitly set mode, esp defaults to STA+AP
    WiFiManager wm;
    //reset settings - for testing
    //wm.resetSettings();
    // set configportal TIMEOUT
    wm.setConfigPortalTimeout(TIMEOUT);
    if (!wm.startConfigPortal(APEsp32)) {
        DEBUG_PRINTLN("failed to connect and hit TIMEOUT");
        delay(3000);
        //reset and try again, or maybe put it to deep sleep
        ESP.restart();
        delay(5000);
    }else{
      WiFi.setSleep(false);
    }
    //if you get here you have connected to the WiFi
    DEBUG_PRINTLN("connected...yeey :)");
}
