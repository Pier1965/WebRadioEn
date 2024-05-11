// Gestione del touch screen NEXTION
bool initNex();
void pvsBtnNex(void *ptr);
void nxtBtnNex(void *ptr);
void vdnBtnNex(void *ptr);
void vupBtnNex(void *ptr);
// Inizializzazione Nextion
bool initNex(){
    if(!nexInit()){
    DEBUG_PRINTLN("Errore di inizializzazione Nextion");
    return false;
  }
  pvsBtn.attachPop(pvsBtnNex, &pvsBtn);
  nxtBtn.attachPop(nxtBtnNex, &nxtBtn);
  vdnBtn.attachPop(vdnBtnNex, &vdnBtn);
  vupBtn.attachPop(vupBtnNex, &vupBtn);
  DEBUG_PRINTLN("NEXTION inizializzato");
  return true;
}
void pvsBtnNex(void *ptr){
  DEBUG_PRINTLN("Previous Station Nextion");
  if(STATION>0)
      STATION--;
    else
      STATION = NR-1;
    nxtButton = 0;
    prvButton = 1;
}
void nxtBtnNex(void *ptr){
  DEBUG_PRINTLN("Next Station Nextion");
    if(STATION<NR-1)
      STATION++;
    else
      STATION = 0;
    nxtButton = 1;
    prvButton = 0;
}
void vdnBtnNex(void *ptr){
  DEBUG_PRINTLN("Vol Up Nextion");
  VOLUME > DVOL ? VOLUME -= DVOL : VOLUME = 0;
}
void vupBtnNex(void *ptr){
  DEBUG_PRINTLN("Vol Down Nextion");
  VOLUME < (100 - DVOL) ? VOLUME += DVOL : VOLUME = 100;
}