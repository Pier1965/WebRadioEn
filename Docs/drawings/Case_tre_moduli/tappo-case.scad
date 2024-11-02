include <dimensioni.h>
module tappocase(){
    difference(){
    union(){
         //bordo usb
        translate([xusbhole,yusbhole,0.01])
            linear_extrude(1.8*S)
                square([wusbhole+sbusb,husbhole+sbusb],true);
difference(){
union(){
 translate([rr,rr,0]){
            linear_extrude(S){
                minkowski(){
                    square(L-2*rr,false);
                    circle(rr);
                }
            }
        }
        
         translate([rr,rr,S]){
            linear_extrude(S){
                minkowski(){
                    square(L-2*(rr),false);
                    circle(rr-S/2-0.2);
                }
            }
        }
    }
    //Alleggerimento
    lall=L-2*rr-2*S-1;
    wall=L-2*rr-2*S-25;
     translate([L/2-wall/2,L/2-lall/2,S]){
            linear_extrude(S+0.1){
                minkowski(){
                    square([wall,lall],false);
                    circle(rr);
                }
            }
        }
        translate([L/2-lall/2,L/2-wall/2,S]){
            linear_extrude(S+0.1){
                minkowski(){
                    square([lall,wall],false);
                    circle(rr);
                }
            }
        }
    // Fori per viti
        rv=1.8;
    translate([rr,rr,-S/2])
    linear_extrude(3*S)
    circle(rv);
    translate([rr,L-rr,-S/2])
    linear_extrude(3*S)
    circle(rv);
    translate([L-rr,rr,-S/2])
    linear_extrude(3*S)
    circle(rv);
    translate([L-rr,L-rr,-S/2])
    linear_extrude(3*S)
    circle(rv);
     //Scassi teste
        rsc=3.5;
        psc=2.7;
        translate([rr,rr,-0.1])
    linear_extrude(psc)
    circle(rsc);
    translate([rr,L-rr,-0.1])
    linear_extrude(psc)
    circle(rsc);
    translate([L-rr,rr,-0.1])
    linear_extrude(psc)
    circle(rsc);
    translate([L-rr,L-rr,-0.1])
    linear_extrude(psc)
    circle(rsc);
    //Foro passaggio spina alimentazione
    translate([L/3,10,-1])
    cylinder(h=6*S,r=4,center=false);
    //Foro passaggio switch radio/orologio
    translate([L*2/3,10,-1])
    cylinder(h=6*S,r=2.4,center=false);
}
}
   
    // foro passaggio usb
    translate([xusbhole,yusbhole,-5*S])
        linear_extrude(10*S)
            square([wusbhole,husbhole],center=true);

}
}
//tappocase();