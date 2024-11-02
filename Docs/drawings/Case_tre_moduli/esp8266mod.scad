//ESP32 Wroom
include<dimensioni.h>
////////////////////////////
module esp32(){
difference(){
    union(){
        // Basetta
        linear_extrude(th)
            square([l,w]);
        //cpu
        translate([xcpu,ycpu,th])
            linear_extrude(3)
                square([18,16]);   
        //usb
        translate([-0.8,w/2-wusb/2,th])
            rotate([90,0,90])
                linear_extrude(lusb)
                    square([wusb,thusb]);         
        // Pin
        for(j=[0:1]){
            for(i=[0:18]){
                // Pin
                translate([xpin+i*passo,ypin+j*dwpin,-lpin+th+1.5])
                    linear_extrude(lpin)
                        square(wpin,true);
                // base pin
                translate([xpin+i*passo,ypin+j*dwpin,-hbp])
                    cylinder($fn=8,h=hbp,r=rbp);
            }
        }
    }
    // Fori di fissaggio
    translate([(w-dfw)/2,(l-dfl)/2,-th])
        linear_extrude(3*th)
            circle(rf,$fn=50);
    translate([(w-dfw)/2+dfl,(l-dfl)/2,-th])
        linear_extrude(3*th)
            circle(rf,$fn=50);
    translate([(w-dfw)/2,(l-dfl)/2+dfw,-th])
        linear_extrude(3*th)
            circle(rf,$fn=50);
    translate([(w-dfw)/2+dfl,(l-dfl)/2+dfw,-th])
        linear_extrude(3*th)
            circle(rf,$fn=50);
}
}

//esp32();