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
#include "oled.h"
// Lettore IR
#include "ir.h"
// Gestione del file con i dati delle stazioni memorizzate
#include "handleStationsFile.h"
// Web Server
#include "handleWebServer.h"

