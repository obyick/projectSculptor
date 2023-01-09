#include "cutBox.h"

//method constructor
cutBox::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    //coordinates
    this -> x0 = x0; this -> x1 = x1;
    this -> y0 = y0; this -> y1 = y1;
    this -> z0 = z0; this -> z1 = z1;
}

//draw overload
void cutBox::draw(Sculptor &s){
    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k < z1; k++){
                s.cutVoxel(i, j, k);
            }
        }
    }
}
