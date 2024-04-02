/*
Wiring:
  ---------------------
  | VS1053  |  ESP32  |
  ---------------------
  |   SCK   |  IO18   |
  |   MISO  |  IO19   |
  |   MOSI  |  IO23   |
  |   XRST  |  EN     |
  |   CS    |  IO5    |
  |   DCS   |  IO0    |
  |   DREQ  |  IO4    |
  |   5V    |  5V     |
  |   GND   |  GND    |
  ---------------------

  ---------------------------
  | JMDO 96C-1 OLED | ESP32 |
  ---------------------------
  | SDA             | 21    |
  | SCL             | 22    |
  | GND             | GND   |
  | 5V              | 5V    |
  ---------------------------

  ---------------------------
  | IR module elegoo | ESP32 |
  ---------------------------
  | G                | GND   |
  | R                | 5V    |
  | Y                | G26   |
  ----------------------------

 ----------------------------
  | Pulsanti         | ESP32  |
  ----------------------------
  | Vol UP           | G32    |
  | Vol Down         | G33    |
  | Next Station     | G13/34 | wroom/wrover - B ttgo
  | Prv Station      | G12    |
  | Radio-Clock Sel  | G36/35 | wroom/wrover - B ttgo
  ----------------------------
*/

const int previousButton  	= 12;
#ifdef WROVER
  const int nextButton      = 34;
#endif
#ifdef WROOM
  const int nextButton      = 13;
#endif
const int volumeUp        	= 32;
const int volumeDown      	= 33;
#ifdef WROVER
  const int RCSelector   		  = 35; // Selettore modalità radio o clock Wrover
#endif
#ifdef WROOM
  const int RCSelector   		  = 36; // Selettore modalità radio o clock Wroom
#endif
//IR sensor
//Infrarosso collegato a Pin Esp32
const unsigned int kRecvPin		= 26;

