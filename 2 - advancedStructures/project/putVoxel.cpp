#include "putVoxel.h"

//method constructor
putVoxel::putVoxel(int x, int y, int z, float r, float g, float b, float a){
    this->x = x; this->y = y; this->z = z; //coordinates

    //colors and transparency
    this->r = r; this->g = g;
    this->b = b; this->a = a;
}

putVoxel::~putVoxel(){} //method destructor

void putVoxel::draw(Sculptor &s){
    s.setColor(r, g, b, a);
    s.putVoxel(x, y, z);
}
