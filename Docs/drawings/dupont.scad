//Dupont femmina
module dupont(n=1){
    passo=2.54;
    w=0.5;
     h=8.5;
     lp=3;
    N= n<1?  1 : n;
    for(i=[0:N-1]){
        translate([0,i*passo,0])
            union(){       
                difference(){
                    linear_extrude(h)
                        square(passo,true);
                    translate([0,0,h-lp])
                        linear_extrude(1.2*lp)
                            square(1.5*w,true);        
                }       
                translate([0,0,-lp])
                    linear_extrude(lp)
                        square(w, true);
            }
    }
}
//dupont(10);