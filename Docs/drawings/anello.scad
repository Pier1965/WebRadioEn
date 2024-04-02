// Anello di fissaggio retina di protezione
include<dimensioni.h>
module anello(){
$fn=100;
difference(){
    union(){
cylinder(h=Ha, r=Rea);
    translate([Rffa,0,Ha-0.01])
    cylinder(h=Hsv,r=Rsv+1);
     translate([0,Rffa,Ha-0.01])
    cylinder(h=Hsv,r=Rsv+1);
         translate([0,-Rffa,Ha-0.01])
    cylinder(h=Hsv,r=Rsv+1);
        translate([-Rffa,0,Ha-0.01])
    cylinder(h=Hsv,r=Rsv+1);
    }
cylinder(h=Ha*3,r=Ria, center=true);
    //Fori passaggio viti M3
    translate([Rffa,0,-1])
    cylinder(h=Ha*3,r=rffaa);
     translate([-Rffa,0,-1])
    cylinder(h=Ha*3,r=rffaa);
    translate([0,Rffa,-1])
    cylinder(h=Ha*3,r=rffaa);
     translate([0,-Rffa,-1])
    cylinder(h=Ha*3,r=rffaa);
    //scasso retina
    translate([0,0,-0.05])
    cylinder(h=0.2,r=rffaa+Rffa+1);
    //scassi teste viti
    translate([Rffa,0,Ha])
    cylinder(h=Hsv,r=Rsv);
    translate([-Rffa,0,Ha])
    cylinder(h=Hsv,r=Rsv);
     translate([0,Rffa,Ha])
    cylinder(h=Hsv,r=Rsv);
    translate([0,-Rffa,Ha])
    cylinder(h=Hsv,r=Rsv);
}
}
anello();