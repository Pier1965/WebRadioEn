bool WMode, oldWMode;
// Timer
unsigned long elapsedTime;
// Numero di stazioni temporaneo
// Numero di stazioni effettivo verrà recuperato dal file degli streams
unsigned char NR = 2;
// Debouncing parameters
long debT = 200; //Debouncing Time in Milliseconds
// definizione pin 
#include "gpio.h"
// Volume e stazioni
unsigned int STATION = 0;
unsigned int OLDSTATION = STATION;
int nxtButton = 1;
int prvButton = 0;
unsigned int VOLUME = 50;
unsigned int OLDVOLUME = VOLUME;
// Server NTP e costanti trattamento ora e giorno
const char* ntpServer= "pool.ntp.org";
const long  gmtOffset_sec = 3600;   // Eastern Standard Time
const int   daylightOffset_sec = 3600;
bool gotTime = false;
unsigned long startMillis;
unsigned long currentMillis;
const unsigned long updateTime = 60000; // 1 min aggiorno orologio su scr
//int timeout = 120; // seconds to run for
// gestione valori di input da pagina web per gestione degli stream
const char* PARAM_INPUT_1 = "pos1Delete";
const char* PARAM_INPUT_2 = "pos2Swap";
const char* PARAM_INPUT_3 = "pos3Swap";
const char* PARAM_INPUT_4 = "pos4AddStream";
const char* PARAM_INPUT_5 = "stream5AddStream";
const char* PARAM_INPUT_6 = "cerca6CercaKeyword";
const char* PARAM_INPUT_7 = "nomeStazione";
const char* PARAM_INPUT_8 = "genereStazione";
///
const char *url;
unsigned long startWsMillis = 0;
unsigned long currentWsMillis = 0;
const unsigned long updateWsTime = 60000; // aggiornamento websocket 
// Inizializzazione NEXTION
bool nexExists = false;