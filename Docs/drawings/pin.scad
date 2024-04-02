//pin
include<dimensioni.h>
module pin(){
    union(){
        translate([0,0,-lpin2])
            linear_extrude(lpin)
                square(wpin,true);
        // base pin
        cylinder($fn=8,h=hbp,r=rbp);
    }
}
//pin();