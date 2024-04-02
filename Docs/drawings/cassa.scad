include <dimensioni.h>
include <moduli.h>
/************************************/
module cassa(){
difference(){
union(){
    //Raccordi di rinforzo base
    translate([S,1.5*rr+(L-3*rr),S])
    rotate([90,0,0])
    raccordo(rr,L-3*rr);

    translate([1.5*rr,S,S])
    rotate([90,0,90])
    raccordo(rr,L-3*rr);

    translate([S+L-2*S,1.5*rr,S])
    rotate([90,0,180])
    raccordo(rr,L-3*rr);

    translate([L-3*rr+1.5*rr,S+L-2*S,S])
    rotate([90,0,-90])
    raccordo(rr,L-3*rr);

    //Rinforzi per viti chiusura tappo
    translate([rr,rr,L-S-S])
        rotate([180,0,-45])
            insertovite(rr,3*rr);

    translate([rr,rr+L-2*rr,L-S-S])
        rotate([180,0,-135])
            insertovite(rr,3*rr);

    translate([rr+L-2*rr,rr+L-2*rr,L-S-S])
        rotate([180,0,-45+180])
            insertovite(rr,3*rr);

    translate([rr+L-2*rr,rr,L-S-S])
        rotate([180,0,-45+180-90])
            insertovite(rr,3*rr);

    difference(){ 
        //La scatola è alta L meno il tappo S
        //Pieno
            translate([rr,rr,0]){
                linear_extrude(L-S){
                    minkowski(){
                        square(L-2*rr,false);
                        circle(rr);
                    };
                };
            }
        //Sottraggo per svuotare
        translate([rr,rr,S]){
            linear_extrude(L-S){
                minkowski(){
                    square(L-2*rr,false);
                    circle(rr-S);
                };
            };   
        }
        //Sottraggo il dentino superiore per 
        //inserire metà spessore del tappo chiusura
        //spesso 2S
        translate([rr,rr,L-S-S]){
            linear_extrude(3){
                minkowski(){
                    square(L-2*rr,false);
                    circle((rr+rr-S)/2);
                 };
            };
        };
       
    };
    
}

//Sottraggo il foro per l'altoparlante
       translate([L/2,L/2,0])
            rotate([0,0,0])
                cylinder(4*S,Ralt+dRalt,Ralt+dRalt,true);
        translate([L/2,L/2,S/2])
            rotate([0,0,0])
                cylinder(4*S,(Ralt+ddRalt),(Ralt+ddRalt));
 //Sttraggo foro passaggio incastro  laterale 
                translate([-S,L/2,L/2])
                    rotate([0,90,0])
                        cylinder($fn=6,3*S,Rf+dRf,Rf+dRf);
//Fori fissaggio anello retina altoparlante
            translate([L/2-Rffa,L/2,0])
                cylinder(h=4*S,r=rffaa,center=true);
             translate([L/2+Rffa,L/2,0])
                cylinder(h=4*S,r=rffaa,center=true);
            translate([L/2,L/2+Rffa,0])
                cylinder(h=4*S,r=rffaa,center=true);
            translate([L/2,L/2-Rffa,0])
                cylinder(h=4*S,r=rffaa,center=true);
}
}

//cassa();
