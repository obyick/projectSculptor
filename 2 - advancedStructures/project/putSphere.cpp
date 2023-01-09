#include <cmath>

#include "putSphere.h"

//method constructor
putSphere::putSphere(int x, int y, int z, int radius,
               float r, float g, float b, float a){
    this -> x = x; this -> y = y; this -> z = z; this -> radius = radius; //coordinates

    //colors and transparency
    this->r = r; this->g = g;
    this->b = b; this->a = a;
}

putSphere::~putSphere(){} //method destructor

//draw overload
void putSphere::draw(Sculptor &s){
    s.setColor(r, g, b, a);
    for(int i = 0; i < x + radius; i++){
        for(int j = 0; j < y + radius; j++){
            for(int k = 0; k < z + radius; k++){
                if((pow(i - x, 2) + pow(j - y, 2) + pow(k - z, 2)) < pow(radius, 2)){
                    s.putVoxel(i, j, k);
                }
            }
        }
    }
}
