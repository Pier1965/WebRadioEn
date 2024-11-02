//IR codifica tasti
//#define APPLE_IR
//#define ELEGO_IR
//#define SAMS_IR
//#define CARMP3
//#define PHILIPSRC5340
//#define KC808
//#define TANIX //SMART TV BOX TANIX TX5 MAX
#define ZODIAC
#ifdef ZODIAC
  #define IR_UP 0xFF7887
  #define IR_UP1 0xF63C8657
  #define IR_DN 0xFF6897
  #define IR_DN1 0xC101E57B
  #define IR_NX 0xFF708F
  #define IR_NX1 0x44C407DB
  #define IR_PV 0xFF28D7
  #define IR_PV1 0x13549BDF
  #define IR_RS 0xFFEA15
  #define IR_RS1 0xA6C4637B

  #define IR_00 0xFFAA55
  #define IR_01 0xFFDA25
  #define IR_02 0xFFF20D
  #define IR_03 0xFFCA35
  #define IR_04 0xFF5AA5
  #define IR_05 0xFFF00F
  #define IR_06 0xFF7A85
  #define IR_07 0xFF6A95
  #define IR_08 0xFF728D
  #define IR_09 0xFF4AB5
#endif

#ifdef TANIX
  #define IR_UP 0x202D02F
  #define IR_UP_ALT 0x20218E7
  #define IR_DN 0x202708F
  #define IR_DN_ALT 0x202E817
  #define IR_NX 0x2028877
  #define IR_PV 0x20208F7
  #define IR_RS 0x202B24D
  #define IR_MUTE 0x202C23D

  #define IR_00 0x20200FF
  #define IR_01 0x202807F
  #define IR_02 0x20240BF
  #define IR_03 0x202C03F
  #define IR_04 0x20220DF
  #define IR_05 0x202A05F
  #define IR_06 0x202609F
  #define IR_07 0x202E01F
  #define IR_08 0x20210EF
  #define IR_09 0x202906F
#endif

#ifdef KC808
  #define IR_UP 0xF700FF
  #define IR_DN 0xF720DF
  #define IR_NX 0xF740BF
  #define IR_PV 0xF7807F
  #define IR_RS 0xF738C7

  #define IR_00 0xF728D7
  #define IR_01 0xF710EF
  #define IR_02 0xF7906F
  #define IR_03 0xF750AF
  #define IR_04 0xF730CF
  #define IR_05 0xF7B04F
  #define IR_06 0xF7708F
  #define IR_07 0xF708F7
  #define IR_08 0xF78877
  #define IR_09 0xF748B7
#endif
#ifdef CARMP3
  #define IR_UP 0xFFA857
  #define IR_DN 0xFFE01F
  #define IR_NX 0xFF02FD
  #define IR_PV 0xFF22DD
  #define IR_RS 0xFF906F

  #define IR_00 0xFF6897
  #define IR_01 0xFF30CF
  #define IR_02 0xFF18E7
  #define IR_03 0xFF7A85
  #define IR_04 0xFF10EF
  #define IR_05 0xFF38C7
  #define IR_06 0xFF5AA5
  #define IR_07 0xFF42BD
  #define IR_08 0xFF4AB5
  #define IR_09 0xFF52AD
  #define IR_100 0xFF9867
  #define IR_200 0xFFB04F
#endif
#ifdef PHILIPSRC5340
  #define IR_UP 0x10458
  #define IR_DN 0x10459
  #define IR_NX 0x1045B
  #define IR_PV 0x1045A
  #define IR_RS 0x104C7

  #define IR_00 0x10400
  #define IR_01 0x10401
  #define IR_02 0x10402
  #define IR_03 0x10403
  #define IR_04 0x10404
  #define IR_05 0x10405
  #define IR_06 0x10406
  #define IR_07 0x10407
  #define IR_08 0x10408
  #define IR_09 0x10409
#endif
#ifdef APPLE_IR
  #define IR_UP 0x77E1D009
  #define IR_DN 0x77E1B009
  #define IR_NX 0x77E1E009
  #define IR_PV 0x77E11009
  #define IR_RS 0x77E14009
#endif
#ifdef ELEGO_IR
  #define IR_UP 0xFF629D
  #define IR_DN 0xFFA857
  #define IR_NX 0xFFC23D
  #define IR_PV 0xFF22DD
  #define IR_RS 0xFFA25D

  #define IR_00 0xFF6897
  #define IR_01 0xFF30CF
  #define IR_02 0xFF18E7
  #define IR_03 0xFF7A85
  #define IR_04 0xFF10EF
  #define IR_05 0xFF38C7
  #define IR_06 0xFF5AA5
  #define IR_07 0xFF42BD
  #define IR_08 0xFF4AB5
  #define IR_09 0xFF52AD

#endif
#ifdef SAMS_IR
  #define IR_UP 0xE0E0E01F
  #define IR_DN 0xE0E0D02F
  #define IR_NX 0xE0E048B7
  #define IR_PV 0xE0E008F7
  #define IR_RS 0xE0E040BF
#endif
