//include <case.scad>
include<case_small.scad>
include <cassa.scad>
include<forchetta.scad>
include<tappo-case.scad>
include<esp32_wroom.scad>
include<millefori.scad>
include<dupont.scad>
include<anello.scad>

// Case radio
color("white")
    case();

// Casse laterali
translate([L,0,0])
    color("magenta")
    cassa();
    
translate([0,L,0])
    rotate([0,0,180])
    color("magenta")
        cassa();
  
 color("green")
 translate([S+L,wf/2+L/2,L-2*S])
 rotate([90+180,0,90+180])
 forchetta();
 
 color("green")
 translate([-S,-wf/2+L/2,L-2*S])
 rotate([90+180,0,90])
 forchetta();
 

  //Blocco esp32, millefori con dupont
 translate([0,S+7*S,0]){ 
 color("green")
    translate([w/2+L/2,hdup+hbp,lmf+S+5*passo])
        rotate([-90,90,0])
            esp32();
 
 translate([L/2-wmf/2,0,S+5*passo])
    color("red")
        rotate([90,0,0])
            basettamf();

color("yellow"){
    translate([L/2-dpw/2+dpw+2*passo,0,lmf+S-2*passo+5*passo])
        rotate([-90,0,0])
            dupont(19); 
    translate([L/2-dpw/2-2*passo,0,lmf+S-2*passo+5*passo])
        rotate([-90,0,0])
            dupont(19);
    
    translate([L/2-dpw/2+dpw,0,lmf+S-2*passo+5*passo])
        rotate([-90,0,0])
            dupont(19); 
    translate([L/2-dpw/2,0,lmf+S-2*passo+5*passo])
        rotate([-90,0,0])
            dupont(19);
}
}
 /*
 color("blue",1)
 translate([L,0,L])
 rotate([0,180,0])
 tappocase();
 */
// Anello retina protezione
color("white")
translate([-L/2,L/2,0])
rotate([180,0,0])
anello();

color("white")
translate([3*L/2,L/2,0])
rotate([180,0,0])
anello();

 