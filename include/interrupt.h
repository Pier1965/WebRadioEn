// Tutti gli interrupt su fronte di discesa
// Gestione pulsanti via interrupt modalita clock <-> radio

void IRAM_ATTR RCSelectorButtonInterrupt() {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    portENTER_CRITICAL_ISR(&mux);
        if (interrupt_time - last_interrupt_time > debT){
            // cambiare stato di funzionamento
            oldWMode = WMode;
            WMode = !WMode;
            last_interrupt_time = interrupt_time;
            #ifdef DEBUG
            DEBUG_PRINT("Modalita funzionamento: ");
            if (WMode)
                DEBUG_PRINTLN("RADIO");
            else
                DEBUG_PRINTLN("CLOCK");
        #endif
        }
    portEXIT_CRITICAL_ISR(&mux);
}

// Gestione pulsanti via interrupt cambio canale

void IRAM_ATTR previousButtonInterrupt() {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    portENTER_CRITICAL_ISR(&mux);
        if (interrupt_time - last_interrupt_time > debT){
            if(STATION>0)
                STATION--;
            else
                STATION = NR-1;
            last_interrupt_time = interrupt_time;
            nxtButton = 0;
            prvButton = 1;
        }
    portEXIT_CRITICAL_ISR(&mux);
    DEBUG_PRINTLN("Prev");
    DEBUG_PRINTDEC(STATION);
    DEBUG_PRINTLN("");
}

void IRAM_ATTR nextButtonInterrupt() {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    portENTER_CRITICAL_ISR(&mux);
        if (interrupt_time - last_interrupt_time > debT){
            if(STATION<NR-1)
                STATION++;
            else
                STATION = 0;
            nxtButton = 1;
            prvButton = 0;
            last_interrupt_time = interrupt_time;
        }
    portEXIT_CRITICAL_ISR(&mux);
    DEBUG_PRINTLN("Next");
    DEBUG_PRINTDEC(STATION);
    DEBUG_PRINTLN("");
}


// Gestione pulsanti via interrupt regolazione volume

void IRAM_ATTR volumeDownInterrupt() {
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    portENTER_CRITICAL_ISR(&mux);
        if (interrupt_time - last_interrupt_time > debT){
            if(VOLUME > DVOL)
                VOLUME -= DVOL;
            else
                VOLUME = 0;
            last_interrupt_time = interrupt_time;
        }
    portEXIT_CRITICAL_ISR(&mux);
}

void IRAM_ATTR volumeUpInterrupt(){
    static unsigned long last_interrupt_time = 0;
    unsigned long interrupt_time = millis();
    portENTER_CRITICAL_ISR(&mux);
        if (interrupt_time - last_interrupt_time > debT){
            if(VOLUME < (100 - DVOL))
                VOLUME += DVOL;
            else
                VOLUME = 100;
            last_interrupt_time = interrupt_time;
        }
    portEXIT_CRITICAL_ISR(&mux);
}
// Gestione pulsanti via interrupt cambio canale e volume

void setupInt(){
    pinMode(previousButton, INPUT_PULLUP);
    pinMode(nextButton, INPUT_PULLUP);
    #ifdef HWRCampli
        pinMode(HWRC, OUTPUT);
    #endif
    attachInterrupt(digitalPinToInterrupt(previousButton), previousButtonInterrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(nextButton), nextButtonInterrupt, FALLING);

    pinMode(volumeUp, INPUT_PULLUP);
    pinMode(volumeDown, INPUT_PULLUP);

    attachInterrupt(digitalPinToInterrupt(volumeUp), volumeUpInterrupt, FALLING);
    attachInterrupt(digitalPinToInterrupt(volumeDown), volumeDownInterrupt, FALLING);

    pinMode(RCSelector, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(RCSelector), RCSelectorButtonInterrupt, FALLING);
}
