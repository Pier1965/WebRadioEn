//Raccordi di rinforzo interni
module raccordo(r=1, lun=1){
    linear_extrude(lun){
        difference(){
            square(2*r);
            translate([r,0,0])
                square(2*r);
            translate([0,r,0])
                square(2*r);
            translate([r,r,0])
                circle(r);
        };
    };
};
//Rinforzi per le viti di chiusura
module insertovite(r=1,h=1){
    difference(){
        cylinder(4*r,r,r,false);
        translate([0,-r,0])
            rotate([atan2(4*r,2*r),0,0])
                linear_extrude(height = 3*r)
                    square(10*rr,true);
        translate([0,0,-0.1])
        cylinder(10.1,1.5,1.5);
    }
};
