include <dimensioni.h>
module tappocassa(){
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
    lall=0.65*L;
    wall=lall-2*rr;
     translate([L/2-wall/2,L/2-wall/2,S]){
            linear_extrude(S+0.1){
                minkowski(){
                    square(wall,false);
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
}
}

tappocassa();