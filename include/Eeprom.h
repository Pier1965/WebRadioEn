// Gestione dei valori da memorizzare al cambio volume, canale e stato di funzionamento allo spegnimento
void restoreEeprom(){
    // gestione pulsanti
    DEBUG_PRINTLN("Recupero i dati di volume e stazione da eprom");
    EEPROM.begin(EEPROM_SIZE);
    DEBUG_PRINTLN("Eprom inizializzata");
    STATION = EEPROM.read(0);
    DEBUG_PRINT("Stazione: ");
    DEBUG_PRINTLN(STATION);
    if(STATION > NR-1){
        STATION = 0;
        EEPROM.write(0, STATION);
    }
    OLDSTATION = STATION;
    nxtButton = 1;
    prvButton = 0;
    // Default volume
    VOLUME = EEPROM.read(1);
    if(VOLUME > 100){
        VOLUME = 100;
        EEPROM.write(1, VOLUME);
    }
    OLDVOLUME = VOLUME;
    DEBUG_PRINT("Volume: ");
    DEBUG_PRINTLN(VOLUME);
    EEPROM.commit();
    DEBUG_PRINTLN("Dati recuperati da eeprom");
}

void updateEeprom(){
    EEPROM.write(0, STATION);
    EEPROM.write(1, VOLUME);
    EEPROM.commit();
}
