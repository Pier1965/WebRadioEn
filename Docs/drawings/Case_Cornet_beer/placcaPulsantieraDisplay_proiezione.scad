// Proiezione dall'alto da quotare in dxf
include <dimensioni.txt>
projection(cut=true) 
    translate([0,0,-Sp/2])
        import("placcaPulsantieraDisplay.stl");