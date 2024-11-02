/*
  Web radio con ESP32

  Pierpaolo Garofalo - http://pier.unirc.eu
  Licensed under GNU GPL v3
 //=================================================================================
27/04/2021
1) Gestisce immissione cambio stazioni e volume tramite pulsanti HW con debouncing SW e HW  (v)
2) Memorizza Stazion e Volume in eeprom                                                     (v)
Otto baroque si sente a volte bene e a volte con singhiozzo a buffer 64, con 32 pare liscio
28/04/2021
3) Interfaccia OLED con info rete e canale                                                  (v)
4) Telecomando IR di vari tipi per cambio stazione e volume                                 (v)
5) Orario e data in OLED                                                                    (v)
01/05/2021
6) Modalità radio oppure orologio
08/05/21
7) Pare risolta questione BBC #208 https://www.youtube.com/watch?v=aMS4XwEr8s0&t=51s
  Nei commenti di random sporadic projects
  Fine 2023 BBC è passata a HSL :-(
8) Aggiunto digit a orari inferiori alle 9
09/05/2021
9) Modificata gestione ora. Se l'orario è stato ottenuto in avvio da NTP non usiamo di nuovo la connessione alla rete
10) Multiwifi per connettersi a piu reti wifi e riconnessione corretta nel caso si perda il collegamento
10/05/21
11) Quando si cambia modalità da Clock a Radio riconnettere wifi e stazione e viceversa
12/05/2021
12) Implementato ring buffer per risolvere Otto Baroque a 320kbps che balbetta... pare funzionare
04/05/2022
    Ringbuffer e abbandonato sia con libreria originale (mio metodo) che librerie di Cellies (disabilitare PSRAM)
    a causa dei continui buffer underrun con Komsomolskaia Pravda
    Gennaio 2024
13) Aggiunta gestione tasti da 0-9 IR con telecomandi che li prevedono (Elegoo)
14) Aggiunta gestione SSID e passwordtramite portale AP 192.168.4.1: in modalità clock
    schiacciare il pulsante VolUp e collegarsi alla rete WebRadioAP e impostare SSID e password di rete
    08/02/2024
15) Eliminato l'hard code di SSID e Password: tolto multiwifi e messo wifimanager
    09/02/2024
16) OLED, IR, Tasti, e modalità di funz OK
    6/02/2024
17) Correzione aggiornamento della data ora locale che non prevedeva il settaggio LOCALE
18) Passaggio alla libreria
      baldram/ESP_VS1053_Library
      celliesprojects/ESP32_VS1053_Stream@^2.0.6 -> La RAI si risente con queste ... boh
      con cellies però il ring buffer continua a dare underrun con Radio Komsomolskaia
    Eliminato hard coding delle stazioni radio:
    Gestione inserimento stazioni via html: webserver e websocket
    Gestione della lista di radio con funzioni aggiungi, sposta ecc
    Passaggio a platformio con board wrover e wroom
    15/03/2024
19) Gestione tasti telecomando per doppia cifra
    21/03/2024
20) Gestione visualizzazione html ottimale per dispositivi
    17/03/2024 (parziale)
21) Gestione ricerca radio con api Radio-Browser
    https://www.radio-browser.info/
    21/03/2024
22) Aggiunto telecomando IR TANIX smart TV, e KC-808
    22/03/2024
23) Aggiunta possibilità di impostare stazione e volume da browser
    via lista comandi a tendina
    27/03/2024
24) Aggiunta la possibilità di esportare la lista delle radio in formato Json
    ListaRadio.json
    28/03/2024
25) Aggiunta la possibilità di importare la lista delle radio in formato Json
    Per gestire file di dimensione maggiore di 1346b, in WebServer.h
    riga 38)  #define HTTP_DOWNLOAD_UNIT_SIZE 3*1436
    riga 41)  #define HTTP_UPLOAD_BUFLEN 3*1436
    01/04/2024
25)	Aggiunto schermo touch NEXTION NX4832T035_011
  25/04/2024
    Da fare:
    Aggiungere verifica sulla coerenza dei dati Pos.1 Pos.2 immessi per la modifica
    della lista di radio.
    Evitare che all'upload della lista di radio si passi alla
    pagina /upload
    Impostare schermo OLED con caratteri grandi indicazione volume e stazione
    durante cambio stazione e volume
    Aggiungere tasti Mute e Clock/Radio mode da telecomando
    Aggiungere OLED a colori
    xx/xx/xx
//=================================================================================
*/
#include "preproDefine.h"
#include "define.h"
#include "GlobalVar.h"
#include "includeLib.h"
#include "GlobalObject.h"
#include "includeFun.h"
//=================================================================================
void setup()
{
  #ifdef SPION
    Serial.begin(115200);
  #endif
  // Config pin del selettore modalità di funzionamento
  confSelector();
  // Setup schermo : Strano... se messo dopo setupInt fa incartare l'ascolto
  #ifdef SCREEN
    initSCR();
  #endif
    // Inizializzazione del NEXTION se usato
  #ifdef NEXTOUCH
    nexExists = initNex();
  #endif
  // Avvio del wifi. Se non c'è una configurazione ESSD e PW avvia AP su 192.168.1.4
  // per immettere i valori di rete e ip della radio via browser
  // Se non vengono immessi attende 120 sec, va in timeout e si riavvia.
  //=================================================================================
  if (!wifi_connect())
  {
    DEBUG_PRINTLN("Non Connesso...");
    DEBUG_PRINTLN("ESP si riavvia...");
  #ifdef SCREEN
      updateAPSCR(TIMEOUT);
  #endif
    delay(5000);
    ESP.restart();
  }
  // Inizializzazione del file system SPIFF
  //=================================================================================
  if (!SPIFFS.begin(true))
  {
    DEBUG_PRINTLN("File system SPIFF non montato... riavvio");
    delay(5000);
    ESP.restart();
  }
  else
  {
    DEBUG_PRINTLN("File system SPIFF montato!!!!!!!");
  }
  // Inizializzazione file delle radio in un oggetto json
  //=================================================================================
  if (!initRadioFileList())
  {
    DEBUG_PRINTLN("File radio non inizializzato... riavvio");
    delay(5000);
    ESP.restart();
  }
  // Inizializzazione e gestione del web server
  // Invio della pagina principale che accetta richieste GET con i campi di input
  //=================================================================================
  startServer();
  DEBUG_PRINTLN("HTTP server e webSocket started");
  // Recupero dell'ora dal server NTP
  //=================================================================================
  initTime();
  restoreEeprom();
  // Inizializzo il decoder Mp3
  //=================================================================================
  SPI.begin();
  SPI.setHwCs(true);
  SPI.begin(SPI_CLK_PIN, SPI_MISO_PIN, SPI_MOSI_PIN); /* start SPI before starting decoder */
  DEBUG_PRINTLN("SPI avviato");
  if (!stream.startDecoder(VS1053_CS, VS1053_DCS, VS1053_DREQ))
  {
    DEBUG_PRINTLN("Cannot start decoder mp3");
    while (1)
      delay(100);
  }
  DEBUG_PRINTLN("Decoder mp3  avviato");
  if (!stream.isChipConnected())
  {
    DEBUG_PRINTLN("Decoder not connected");
    while (1)
      delay(100);
  };
  DEBUG_PRINTLN("Decoder running");
  delay(100);
  // Setup delle routine di interrupt per i tasti stazone e volume
  //=================================================================================
  setupInt();
  // Inizializza sensore IR
  //=================================================================================
  StartIR();
  delay(100);
  /*
      DEBUG_PRINT("codec: ");
      DEBUG_PRINTLN(stream.currentCodec());
      DEBUG_PRINT("bitrate: ");
      DEBUG_PRINT(stream.bitrate());
      DEBUG_PRINTLN("kbps");
  */
  //
  // Se la levetta è in modalità orologio spegni il wifi
  //=================================================================================
  // Sostituzione della levetta bistabile con un pulsante: all'accensione
  // parto all'accensione  in modalità clock
  //WMode = workingMode();
  WMode = false;
  oldWMode = WMode;
  DEBUG_PRINT("WMode = ");
  DEBUG_PRINTDEC(WMode);
  DEBUG_PRINTLN("");
  if (!WMode)
  {
    #ifdef HWRCampli
      digitalWrite(HWRC, LOW);
    #endif
    DEBUG_PRINTLN("Disconnessione e spegnimento WiFi...");
    WiFi.disconnect(true);
    WiFi.mode(WIFI_OFF);
    #ifdef SCREEN
        updateTimeScr();
    #endif
    #ifdef NEXTOUCH
        updateTimeScr_nex();
    #endif
  }
  else
  {
    #ifdef HWRCampli
      DEBUG_PRINTLN("Spengo amplificatore");
      digitalWrite(HWRC, HIGH);
    #endif
    stream.setVolume(VOLUME);
    JsonObject record = radioRecords[STATION].as<JsonObject>();
    if (record.containsKey(POS2))
    {
      url = record[POS2];
    }
    stream.connecttohost(url);
    DEBUG_PRINT("codec: ");
    DEBUG_PRINTLN(stream.currentCodec());
    DEBUG_PRINT("bitrate: ");
    DEBUG_PRINT(stream.bitrate());
    DEBUG_PRINTLN("kbps");
    #ifdef SCREEN
        updateSCR();
    #endif
    #ifdef NEXTOUCH
        updateSCR_nex();
    #endif
  }
  oldWMode = WMode;
}
// Loop
//=================================================================================
void loop()
{
  server.handleClient();
  webSocket.loop();
  //WMode = digitalRead(RCSelector);
  // Gestione del cambio della modalità di funzionamento
  // RADIO <-> CLOCK
  //=================================================================================
  if (oldWMode != WMode)
  {
    DEBUG_PRINTLN("Modalita funz cambiata");
    oldWMode = WMode;
    // CLOCK -> RADIO
    //=================================================================================
    if (WMode)
    {
      DEBUG_PRINTLN("Modalita radio");
      // Accendo l'ampli audio
      #ifdef HWRCampli
        DEBUG_PRINTLN("Accendo amplificatore");
        digitalWrite(HWRC, HIGH);
      #endif
      // Riaccendo il WIFI
      if (!wifi_connect())
      {
        DEBUG_PRINTLN("Non Connesso...");
        DEBUG_PRINTLN("ESP si riavvia...");
        delay(100);
        #ifdef SCREEN
                updateAPSCR(TIMEOUT);
        #endif
        delay(5000);
        ESP.restart();
      }
      delay(100);
      // Ripristino volume e stazione
      stream.setVolume(VOLUME);
      record = radioRecords[STATION].as<JsonObject>();
      if (record.containsKey(POS2))
      {
        url = record[POS2];
      }
      // Tentativo di connessione alla stazione radio
      while (!stream.connecttohost(url))
      {
        // Da fare: qui devo gestire il caso di mancata connessione a TUTTE le radio
        // in elenco... es i++ ad ogni ciclo fino a NR e poi riavviare?
        DEBUG_PRINTLN("Host non connesso");
        DEBUG_PRINTLN("Cambio stazione");
        delay(1000);
        // Qui gestisco la mancata connessione
        // vedo se l'ultimo cambio di stazione è stato in avanti
        // o in dietro e così cerco nella stessa direzione
        if (nxtButton == 1)
        {
          STATION < (NR - 1) ? STATION++ : STATION = 0;
        }
        else
        {
          STATION > 0 ? STATION-- : STATION = NR - 1;
        }
        updateEeprom();
        record = radioRecords[STATION].as<JsonObject>();
        if (record.containsKey(POS2))
        {
          url = record[POS2];
        }
        DEBUG_PRINTDEC(STATION);
        DEBUG_PRINTLN();
        #ifdef SCREEN
                updateSCR();
        #endif
        #ifdef NEXTOUCH
                updateSCR_nex();
        #endif
      }
      delay(500);
      #ifdef SCREEN
            updateSCR();
      #endif
      #ifdef NEXTOUCH
            updateSCR_nex();
      #endif
    }
    else
    {
      // RADIO -> CLOCK
      //=================================================================================
      // Se si è passati in modalità CLOCK spengo il wifi
      // e cancello l'istanza dello stream
      // Spengo l'amplificatore audio
      #ifdef HWRCampli
        DEBUG_PRINTLN("Spengo amplificatore");
        digitalWrite(HWRC, LOW);
      #endif
      DEBUG_PRINTLN("Disconnessione e spegnimento WiFi...");
      stream.stopSong();
      WiFi.disconnect(true);
      WiFi.mode(WIFI_OFF);
      #ifdef SCREEN
            updateTimeScr();
      #endif
      #ifdef NEXTOUCH
            updateTimeScr_nex();
      #endif
    }
  }
  //=================================================================================
  // Gestione funzionamento in mdalità RADIO
  if (WMode)
  {
    jsonString = "";
    serializeJson(jsonDoc_tx, jsonString);
    while (WMode)
    {
      server.handleClient();
      webSocket.loop();
      // Rimedio al fatto che non riesco a far caricare la lista al caricamento
      // della pagina
      currentWsMillis = millis();
      if (currentWsMillis - startWsMillis > updateWsTime)
      {
        webSocket.broadcastTXT(jsonString);
        startWsMillis = currentWsMillis;
      }
      // Gestione radio in modalità playing
      stream.loop();
      delay(5);
      // check dei comandi NEXTION
      #ifdef NEXTOUCH
            if (nexExists)
              nexLoop(nex_list);
      #endif
      // Check dei tasti e dei comandi IR
      checkIR();
      switch (checkButtons())
      {
      case STNCH:
        stream.stopSong();
        delay(1000);
        record = radioRecords[STATION].as<JsonObject>();
        if (record.containsKey(POS2))
        {
          url = record[POS2];
          DEBUG_PRINTLN(url);
        }
        // Gestione eventuale mancata connessione
        // e cambio del canale. Da gestire mancata connessione a tutti
        // i canali
        while (!stream.connecttohost(url))
        {
          // L'host non è disponibile... cambio canale
          DEBUG_PRINTLN("Host non connesso");
          delay(1000);
          // Qui gestire la mancata connessione
          if (nxtButton == 1)
          {
            STATION < (NR - 1) ? STATION++ : STATION = 0;
          }
          else
          {
            STATION > 0 ? STATION-- : STATION = NR - 1;
          }
          updateEeprom();
          record = radioRecords[STATION].as<JsonObject>();
          if (record.containsKey(POS2))
          {
            url = record[POS2];
          }
        }
        DEBUG_PRINTDEC(STATION);
        DEBUG_PRINTLN();
        #ifdef SCREEN
                updateSCR();
        #endif
        #ifdef NEXTOUCH
                updateSCR_nex();
        #endif
        break;
      case VOLCH:
        stream.setVolume(VOLUME);
        DEBUG_PRINTDEC(VOLUME);
        DEBUG_PRINTLN();
        #ifdef SCREEN
                updateSCR();
        #endif
        #ifdef NEXTOUCH
                updateSCR_nex();
        #endif
        break;
      }
      if (checkTime())
      {
      #ifdef SCREEN
              updateSCR();
      #endif
      #ifdef NEXTOUCH
              updateSCR_nex();
      #endif
      }
    }
  }
  else
  {
    //=================================================================================
    // Funzionamento in modalità CLOCK
    DEBUG_PRINTLN("Orologio");
    while (!checkReset())
    {
      // Gestione radio in modalità orologio
      if (checkTime())
      {
      #ifdef SCREEN
              updateTimeScr();
      #endif
      #ifdef NEXTOUCH
              updateTimeScr_nex();
      #endif
      }
      // In modalità CLOCK schiacciando Volume Up si richiede
      // l'avvio del portale 192.168.4.1 per la gestione
      // del SSID e PW wifi
      if (digitalRead(volumeUp) == HIGH)
      {
        #ifdef SCREEN
                updateAPSCR(TIMEOUT);
        #endif
        delay(100);
        setSsidPw();
      }
    }
  }
}
