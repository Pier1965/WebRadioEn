void setTime(){
        String ore;
        String Giorno;
        getLocalTime(&timeinfo);
        if(timeinfo.tm_mday<10)
            Giorno = "0" + String(timeinfo.tm_mday);
        else
            Giorno = String(timeinfo.tm_mday);
        Data = dow[timeinfo.tm_wday] + " " + Giorno + " " +  months[timeinfo.tm_mon];
        if(timeinfo.tm_hour<10)
            ore = "0" + String(timeinfo.tm_hour);
        else
            ore = String(timeinfo.tm_hour);
        if(timeinfo.tm_min<10)
            minuti = "0" + String(timeinfo.tm_min);
        else
            minuti = String(timeinfo.tm_min);
        Ora = ore + ":" + minuti;
        //updateSCR();
        DEBUG_PRINTLN("Time from Internet  ");
        DEBUG_PRINT(Data);
        DEBUG_PRINT(" - ");
        DEBUG_PRINTLN(Ora);
}

// Recupero dell'ora
void initTime(){
    // Init and get the time
    int nr = 0;         // numero di tentativi
    int ntMax = 5;     //numero di tentativi di connessione al server ntp
    int dt = 1000;      //tempo attesa ri-tentativo
    String ore;
    String Giorno;
    DEBUG_PRINTLN("Syncing time...");
    //configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    configTime(0, 0, ntpServer);
    while(time(nullptr) <= 150000) {
        DEBUG_PRINTLN("Tentativo di recupero orario...");
        nr++;
        if (nr > ntMax) {
	        DEBUG_PRINTLN("Recupero orario fallito...");
            gotTime = false;
		    break;
	    }
        delay(dt);
    }
    if(nr < ntMax){
        DEBUG_PRINTLN("Recupero orario eseguito...");
        gotTime = true;

    }
    setenv("TZ",timezone.c_str(),1);  //  Now adjust the TZ.  Clock settings are adjusted to show the new local time
    tzset();
    !getLocalTime(&timeinfo);
    delay(10);
    if(timeinfo.tm_mday<10)
        Giorno = "0" + String(timeinfo.tm_mday);
    else
        Giorno = String(timeinfo.tm_mday);
    Data = dow[timeinfo.tm_wday] + " " + Giorno + " " +  months[timeinfo.tm_mon];
    if(timeinfo.tm_hour<10)
        ore = "0" + String(timeinfo.tm_hour);
    else
        ore = String(timeinfo.tm_hour);
    if(timeinfo.tm_min<10)
        minuti = "0" + String(timeinfo.tm_min);
    else
        minuti = String(timeinfo.tm_min);
    Ora = ore + ":" + minuti;

    DEBUG_PRINTLN("Time from Internet  ");
    DEBUG_PRINT(Data);
    DEBUG_PRINT(" - ");
    DEBUG_PRINTLN(Ora);

}

bool checkTime(){
    String ore;
    String Giorno;
    currentMillis = millis();  //che ore sono?
    if (currentMillis - startMillis >= updateTime){ //è ora di aggiornare l'ora?
        startMillis = currentMillis;
        if(gotTime){ //Il tentativo di inizializzare l'ora ha avuto successo all'accensione?
            initTime(); // No... riproviamo
        }else{
            time(&now); // Si aggiorniamo senza ricontattare il server NTP
            localtime_r(&now, &timeinfo);
        }
        if(timeinfo.tm_mday<10)
            Giorno = "0" + String(timeinfo.tm_mday);
        else
            Giorno = String(timeinfo.tm_mday);
        Data = dow[timeinfo.tm_wday] + " " + Giorno + " " +  months[timeinfo.tm_mon];
        if(timeinfo.tm_hour<10)
            ore = "0" + String(timeinfo.tm_hour);
        else
            ore = String(timeinfo.tm_hour);
        if(timeinfo.tm_min<10)
            minuti = "0" + String(timeinfo.tm_min);
        else
            minuti = String(timeinfo.tm_min);
        Ora = ore + ":" + minuti;

        DEBUG_PRINTLN("Time from Internet  ");
        DEBUG_PRINT(Data);
        DEBUG_PRINT(" - ");
        DEBUG_PRINTLN(Ora);
        return true;
    }
    return false;
}
