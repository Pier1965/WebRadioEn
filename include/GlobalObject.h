//WiFiMulti wifiMulti; // Er 02
WiFiClient client;
// decoder mp3
//VS1053 player(VS1053_CS, VS1053_DCS, VS1053_DREQ);
ESP32_VS1053_Stream stream;
// Interrupt
portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
// Sensore IR
IRrecv irrecv(kRecvPin);
decode_results results;
// Oled Display
#ifdef OLEDJMDO
  Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
#endif
// Display TFT 2.8 ST7789
#ifdef ST7789
  Arduino_DataBus *bus = new Arduino_ESP32SPI(TFT_DC /* DC */, TFT_CS /* CS */, TFT_SCL /* SCK */, TFT_SDA /* MOSI */, GFX_NOT_DEFINED /* MISO */, VSPI /* spi_num */);
  Arduino_GFX *display = new Arduino_ST7789(  bus, TFT_RST /* RST */, 0 /* rotation */);
#endif
// Ora data
// Inserire qui la timezone come da ->  https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv
// Europe/Rome 	CET-1CEST,M3.5.0,M10.5.0/3
String timezone = "CET-1CEST,M3.5.0,M10.5.0/3";
// Server NTP
//String ntpServer = "pool.ntp.org";
String time_string;
struct tm timeinfo;
time_t now;
  // int tm_sec;
  // int tm_min;
  // int tm_hour;
  // int tm_mday;
  // int tm_mon;
  // int tm_year;
  // int tm_wday;
  // int tm_yday;
  // int tm_isdst;
  String dow[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
  String months[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
  String Data;
  String Ora;
  String minuti;
  // Nome host e AP
String hostname = "ESP32Radio";
const char* APEsp32 = "WebRadioAP";
// Partenza del web server per la gestione delle radio memorizzate
WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);
// inclusione del file pagina web
#include "index.html"
// Gestione file elenco Radio. Non aggiungere il punto "."/radio.txt
String fileRadio = "/radio.txt";
// Documento json in cui memorizzarei dati del file con la lista delle radio
// 50 radio 4 campi
#ifdef WROVER
  #define DIMJSONDOC 25600
#endif
#ifdef WROOM
  #define DIMJSONDOC 12800
#endif
StaticJsonDocument<DIMJSONDOC> jsonDoc_tx;
JsonArray radioRecords = jsonDoc_tx.to<JsonArray>();
// Documento json in cui memorizzarei le posizioni delle stazioni
// da modificare e l'operazione di modifica da fare
// due campi numerici Pos_1 Pos_2 e uno stringa Operation
StaticJsonDocument<200> jsonDoc_rx;
JsonArray radioAlterate = jsonDoc_rx.to<JsonArray>();
JsonObject record;
// Oggetto json stringhificato per comunicazione via websocket
String jsonString = "";
// Oggetti del display touch NEXTION
#ifdef NEXTOUCH
  NexButton pvsBtn = NexButton(0, 2, "b1");
  NexButton nxtBtn = NexButton(0, 3, "b2");
  NexButton vdnBtn = NexButton(0, 4, "b3");
  NexButton vupBtn = NexButton(0, 5, "b4");
  NexTouch *nex_list[] = {
    &pvsBtn,
    &nxtBtn,
    &vdnBtn,
    &vupBtn,
    NULL
  };
#endif

