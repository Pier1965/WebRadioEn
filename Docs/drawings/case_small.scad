include <dimensioni.h>
include <moduli.h>
/************************************/
module case(){
union(){
    difference(){
       union(){
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
        //baionette allineamento e passaggio cavi
        translate([-3*S,L/2,L/2])
            rotate([0,90,0])
                cylinder($fn=6,L+2*3*S,D/2,D/2);
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
        
        //sottraggo i fori passaggio cavi con casse
        translate([L/2,L/2,L/2])
            rotate([0,90,0])
                cylinder(8*S+L,Df/2,Df/2,true);
       //sottraggo l'anello per inserimento forchetta sx di fissaggio
        translate([-2*S,L/2,L/2])
            rotate([0,90,0])
                difference(){
                    cylinder(S,2.5*D/2,2.5*D/2);
                     cylinder(S,A/2,A/2);
        }
         //sottraggo l'anello per inserimento forchetta dx di fissaggio
        translate([L+S,L/2,L/2])
            rotate([0,90,0])
                difference(){
                    cylinder(S,2.5*D/2,2.5*D/2);
                     cylinder(S,A/2,A/2);
        }
        //Sottraggo la finestrella dell'OLED
        translate([colx,coly-dcoly,-1]){
            linear_extrude(5){
                square([Wo,Ho],true);
            translate([0,-ho/2-Ho/2,0])
                square([wo,ho],true);
            }
        }
        //Dentino OLED
        translate([colx,coly-dcoly,1.5]){
            linear_extrude(5){
                square([Wo+2,Ho+8],true);
            translate([0,-ho/2-Ho/2,0])
                square([wo,ho],true);
            }
        }
        // Foro passaggio perno volume
        translate([L/2,L,3/4*L])
            rotate([-90,0,0])
                cylinder(10,dpv/2,dpv/2,true);    
         // Fori passaggio pulsanti
        translate([L/4,L*3/4,0])
            cylinder(10,dp/2,dp/2,true);   
         translate([L*3/4,L*3/4,0])
            cylinder(10,dp/2,dp/2,true);   
        translate([L/4,L/4,0])
            cylinder(10,dp/2,dp/2,true);   
         translate([L*3/4,L/4,0])
            cylinder(10,dp/2,dp/2,true);  
        //Foro di passaggio sensore IR
        translate([L/2-wir/2,L-S-S/2,L/4-hir/2])
            linear_extrude(2*S)
                square([wir,hir]);
        
    };
    
    // Sostegni basetta millefori
    {
        // Sostegno centrale
        {    
            translate([L/2,S-S/2+7*S-smf,0])
            linear_extrude(S+10*passo)
            square([8*passo,S],true);

            translate([L/2,S+7*S-smf/2,0])
            linear_extrude(S+5*passo)
            square([8*passo,smf],true);

            translate([L/2,S-S/2+7*S-smf+S+smf,0])
            linear_extrude(S+10*passo)
            square([8*passo,S],true);
        }
        // Sostegno laterale sx
        {
            translate([0,0,L]){
                rotate([0,90,0]){
                    translate([L/2,S-S/2+7*S-smf,0])
                    linear_extrude(S+7*passo)
                    square([8*passo,S],true);

                    translate([L/2,S+7*S-smf/2,0])
                    linear_extrude(S+6*passo)
                    square([8*passo,smf],true);

                    translate([L/2,S-S/2+7*S-smf+S+smf,0])
                    linear_extrude(S+6.5*passo)
                    square([8*passo,S],true); 
                }
            }
        }
        // Sostegno laterale dx
        {
            translate([L,0,0]){
                rotate([0,-90,0]){
                    translate([L/2,S-S/2+7*S-smf,0])
                    linear_extrude(S+7*passo)
                    square([8*passo,S],true);

                    translate([L/2,S+7*S-smf/2,0])
                    linear_extrude(S+6*passo)
                    square([8*passo,smf],true);

                    translate([L/2,S-S/2+7*S-smf+S+smf,0])
                    linear_extrude(S+6.5*passo)
                    square([8*passo,S],true); 
                }
            }
        }
    }
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
}
}

//case();