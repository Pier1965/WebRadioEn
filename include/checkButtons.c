int checkButtons(){
    if (STATION != OLDSTATION){
      //connectToStation();
      OLDSTATION = STATION;
      updateEeprom();
      DEBUG_PRINT("Stazione: ");
      DEBUG_PRINTLN(STATION);
      return STNCH;
    }
    if (VOLUME != OLDVOLUME){
      //player.setVolume(VOLUME);
      OLDVOLUME = VOLUME;
      updateEeprom();
      DEBUG_PRINT("Volume: ");
      DEBUG_PRINTLN(VOLUME);
      return VOLCH;
    }
    return 0;
}
