//ESP32 Wroom
include<dimensioni.h>
include<pin.scad>
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
        for(j=[0:npw-1]){
            for(i=[0:npl-1]){
                translate([l/2+-(passo*(npl-1))/2+i*passo,w/2-dpw/2+j*dpw,-hbp])
                pin();
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