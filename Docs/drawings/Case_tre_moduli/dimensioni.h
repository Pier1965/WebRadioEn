///////////////// Forma cubica principale ////////////////////////////
// Lato del cubo
L=80;
HC=120;
//Spessore pareti
S=3;
// Raggio di raccordo
rr=10;
//Accuratezza cilindri
$fn=50;
//Foro passaggio cavi
//Circoscrive esagono $fn=6
D=L/3;
//Foro passaggio cavi altoparlanti
Rf=D/4;
Df=2*Rf;
//gioco per compensare il ritiro su foro esagonale
dRf=0.25;
//Oled
colx=L/2;
coly=L/2+1;
dcoly=0;
Wo=26.5;
wo=12;
Ho=19;
ho=3;
// Perno volume
dpv=7;
//Sensore IR
wir=7+0.5;
hir=5+0.5;
// Pulsanti
dp=12;
/////////////////// foro casse ///////////////////////////////
//Altoparlante
Ralt=50.5/2;
//ripresa ritiro
dRalt=0.1;
//Dentino appoggio altoparlante
ddRalt=1.25;
//////////////// Anello cass fissaggio retina ////////////////
Ha=3;
Rea=65/2;
Ria=Ralt-2;
Rffa=Ralt+3;
// Scasso vite
Rsv=3;
Hsv=3;
// Raggio foro fissaggio anello altoparlante vite M3
rffaa=1.5;
//////////////// Forchetta di arresto cubi ///////////////////
//Forchetta blocco casse
A=2*Rf+3;
//gioco su larghezza forchette
//per compensare il ritiro
dA=0.4;
//gioco spessore forchetta
dS=-0.3;
thf=S+dS;
dentey=4;
dentez=2*S;
//larghezza forchette laterali
lf=5;
//ingombro
wf=D+2*lf;
hf=L/2-2*S+D/2;
// Foro passaggio USB in tappo posteriore case
wusbhole=8.5;
husbhole=3.5;
xusbhole=L/2;
yusbhole=S+33+husbhole/2;
//bordino foro
sbusb=3;
///////////////////////// ESP 32 /////////////////////////////
//ESP32 Wroom
//Basetta
//pin
passo=2.54;
//dimensioni basetta wroom
w=11*passo;
l=22*passo;
th=1.5;
//Numero dei pin
npl=19;
//Numero file pin  distanza tra le file
dpw=10*passo;
npw=2;
// Fori di fissaggio
rf=1.25;
dfl=51;
dfw=23.5;
//cpu
wcpu=16;
lcpu=18;
thcpu=3;
xcpu=l-8-lcpu;
ycpu=w/2-wcpu/2;
//usb
wusb=7.4;
thusb=2.5;
lusb=5.8;
// pin a sezione quadrata
wpin=0.5;
lpin1=3;
lpin2=5.5;
lpin=11;
ypin=(w-10*passo)/2;
xpin=(l-18*passo)/2;
dwpin=10*passo;//(w-2*ypin);
//basepin
hbp=2.5;
rbp=passo/2;
/////////////////// basetta millefori ////////////////
//dimensioni basetta
wmf=(16+1)*passo;
//lmf=L-S-S-S;
lmf=23*passo;
//spessore millefori
smf=1.5;
//numero fori
nfy=lmf/passo;
nfx=wmf/passo;
//raggio foro pin
rfmf=sqrt(2*pow(wpin/2,2));
//Dupont
hdup=8.5;
