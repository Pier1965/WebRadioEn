//Volume knob
difference(){        
     cylinder($fn=12,h=15,r1=10,r2=8);
    translate([0,0,15])
rotate([0,90,0])
linear_extrude(20)
circle($fn=3,r=01);
    {
        $fn=50;
        translate([0,0,-0.01])
            cylinder(h=4,r1=6,r2=6);
            cylinder(h=12,r1=3.1,r2=2.8);
    }
}

