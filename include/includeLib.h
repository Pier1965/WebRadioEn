//
#include <Arduino.h>
#include <stdbool.h>
//
// Librerie
#include <WiFiManager.h> // wnatth3/WiFiManager@^2.0.16-rc.2
// HW settings
#include <stdbool.h>
#include <SPI.h>
// Oled Display
#ifdef OLEDJMDO
    #include <Adafruit_GFX.h>
    #include <Adafruit_SSD1306.h>
#endif
#ifdef ST7789
    #include <Arduino_GFX_Library.h>
    #include <font/FreeSans12pt7b.h>
#endif
// Decoder mp3 e stream
#include <VS1053.h>               /* https://github.com/baldram/ESP_VS1053_Library */
#include <ESP32_VS1053_Stream.h>
// Ping per verificare la connessione di rete
#include <ESP32Ping.h>
// Gestione eprom per memorizzare valori di canale e volume
#include <EEPROM.h>
// Gestione sensore a infrarossi
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>
// Eprom
#include <EEPROM.h>
// Pagina web
#include<WebServer.h>
#include<WebSocketsServer.h>
//#include <AsyncTCP.h>  /* use the esphome.io fork*/
//#include <ESPAsyncWebServer.h>  /* use the esphome.io fork*/
// Gestione file system
#include "FS.h"
#include <SPIFFS.h>
#include <ArduinoJson.h>
// Gestione display touch NEXTION NX4832T035_011
#ifdef NEXTOUCH
    #include<Nextion.h>
#endif
