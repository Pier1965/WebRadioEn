/* Piastra anteriore pulsanti e display */
include <dimensioni.txt>
difference(){
    union(){
        // Piastra
        translate([Hp/2,0,0]){
            cylinder($fn=36,Sp,Hp/2,Hp/2);
            translate([Bp-Hp,0,0])
                cylinder($fn=36,Sp,Hp/2,Hp/2);
        }
        translate([Hp/2, -Hp/2,0])
            linear_extrude(Sp)
                square([Bp-Hp,Hp],false);
         // Riferimento inferiore   
        translate([(Bp-Bf)/2, -Hf/2,-Sp])
            linear_extrude(Sp)
                square([Bf,Hf],false);
     }
    // Passaggio display
    translate([Bp/2,0,-2*Sp])
        linear_extrude(4*Sp)
            square([Bd,Hd],true);
    // Foro sensore IR
    translate([Xir, Yir,-3*Sp])
        cylinder($fn=36,6*Sp,Dir/2,Dir/2);
    // Foro pulsante radio <-> clock
    translate([Xprc, Yprc,-3*Sp])
        cylinder($fn=36,6*Sp,Dfp/2,Dfp/2);
    // Foro pulsante volume up
    translate([Xpvup, Ypvup,-3*Sp])
        cylinder($fn=36,6*Sp,Dfp/2,Dfp/2);
    // Foro pulsante volume down
    translate([Xpvdn, Ypvdn,-3*Sp])
        cylinder($fn=36,6*Sp,Dfp/2,Dfp/2);
    // Foro pulsante ch+
    translate([Xpchp, Ypchp,-3*Sp])
        cylinder($fn=36,6*Sp,Dfp/2,Dfp/2);
    // Foro pulsante ch-
    translate([Xpchm, Ypchm,-3*Sp])
        cylinder($fn=36,6*Sp,Dfp/2,Dfp/2);
}