include<dimensioni.h>
include <moduli.h>
module forchetta(){
union(){
    linear_extrude(thf)
        difference(){
        square([wf,hf]);
        translate([wf/2,hf-D/2,0])
            circle((A+dA)/2);
        translate([(wf-(A+dA))/2,hf-(D/2),0])
            square([A+dA,D/2]);
        }
     linear_extrude(dentez)
        square([D+2*lf,dentey]);
        translate([wf,dentey,S+dS])
         rotate([0,-90,0])
            raccordo(r=dentez-S-dS,lun=wf);
    }
}
//forchetta();
