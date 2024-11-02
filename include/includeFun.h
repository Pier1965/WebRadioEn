#include "wifi_conf.h"
// Gestione filesystem SPIFF
#include "initSpiff.h"
//Gestione data e ora
#include "time.h"
#include "datetime.h"
#include "confSelector.h"
// Recupero di dati di volume e stazione da eeprom. Si serve di NR
#include"Eeprom.h"
// Funzione di controllo della variazione dei valori di Volume e Stazione gestiti da interrupt
#include"checkButtons.h"
// Gestione interrupt pulsanti
#include"interrupt.h"
#include "ir_butt.h"
// Inclusione funzioni schermo
// oled
#ifdef OLEDJMDO
  #include "oled.h"
#endif
// TFT 2.8 ST7789
#ifdef ST7789
  #include "ST7789-TFT.h"
#endif
// Lettore IR
#include "ir.h"
// Gestione del file con i dati delle stazioni memorizzate
#include "handleStationsFile.h"
// Web Server
#include "handleWebServer.h"
// inline max, min function
inline int max(int x, int y) {
  return x >= y ? x : y;
}
inline int min(int x, int y) {
  return x <= y ? x : y;
}
// Gestione NEXTION
#ifdef NEXTOUCH
  // Inizializzazione e gestione input bottoni
  #include "handleNextion.h"
  // Gestione output messaggi a schermo
  #include "nexScr.h"
#endif
