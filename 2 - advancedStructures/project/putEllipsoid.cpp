#include <cmath>

#include "putEllipsoid.h"

//method constructor
putEllipsoid::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz,
               float r, float g, float b, float a){
    //coordinates
    this -> xcenter = xcenter; this -> ycenter = ycenter; this -> zcenter = zcenter;
    this -> rx = rx; this -> ry = ry; this -> rz = rz;

    //colors and transparency
    this->r = r; this->g = g;
    this->b = b; this->a = a;
}

putEllipsoid::~putEllipsoid(){} //method destructor

//draw overload
void putEllipsoid::draw(Sculptor &s){
    s.setColor(r, g, b, a);
    for(int i = 0; i < xcenter + rx; i++){
        for(int j = 0; j < ycenter + ry; j++){
            for(int k = 0; k < zcenter + rz; k++){
                if((pow(i - xcenter, 2) / pow(rx, 2)) + (pow(j - ycenter, 2) / pow(ry, 2)) + (pow(k - zcenter, 2) / pow(rz, 2)) < 1){
                    s.putVoxel(i, j, k);
                }
            }
        }
    }
}
