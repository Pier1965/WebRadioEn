//Millefori ESP
include<dimensioni.h>
module basettamf(){
    difference(){
        //basetta
        linear_extrude(smf)
            square([wmf,lmf]);
        //fori
        for(j=[0:nfy-1]){
            for(i=[0:nfx-1]){
                translate([passo/2+i*passo,j*passo,-smf])
                    cylinder(h=3*smf,r=rfmf);
            }
        }
    }
}
//basettamf();