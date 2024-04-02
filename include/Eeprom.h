

void restoreEeprom(){
    // gestione pulsanti
    DEBUG_PRINTLN("Recupero i dati di volume e stazione da eprom");
    EEPROM.begin(EEPROM_SIZE);
    STATION = EEPROM.read(0);
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
    EEPROM.commit();
}

void updateEeprom(){
    EEPROM.write(0, STATION);
    EEPROM.write(1, VOLUME);
    EEPROM.commit();
}
