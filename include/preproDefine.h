//#define TESTWIFI // se settato resetta SSID e PW all'avvio
#define SPION
#define DEBUG
#ifdef DEBUG
    #ifdef SPION
        #define DEBUG_PRINT(x)     Serial.print (x)
        #define DEBUG_PRINTDEC(x)     Serial.print (x, DEC)
        #define DEBUG_PRINTLN(x)  Serial.println (x)
    #endif
#else
  #define DEBUG_PRINT(x)
  #define DEBUG_PRINTDEC(x)
  #define DEBUG_PRINTLN(x)
#endif
// Testare il file delle stazioni memorizzate
// se settato cancella il file delle radio al riavvio
// #define TESTRADIOFILE

