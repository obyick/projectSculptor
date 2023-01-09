#include <cmath>

#include "cutSphere.h"

//method constructor
cutSphere::cutSphere(int x, int y, int z, int radius){
    //coordinates
    this -> x = x; this -> y = y; this -> z = z; this -> radius = radius;
}

//draw overload
void cutSphere::draw(Sculptor &s){
    for(int i = 0; i < x + radius; i++){
        for(int j = 0; j < y + radius; j++){
            for(int k = 0; k < z + radius; k++){
                if((pow(i - x, 2) + pow(j - y, 2) + pow(k - z, 2)) < pow(radius, 2)){
                    s.cutVoxel(i, j, k);
                }
            }
        }
    }
}
