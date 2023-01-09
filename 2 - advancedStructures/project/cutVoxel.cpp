#include "cutVoxel.h"

//method constructor
cutVoxel::cutVoxel(int x, int y, int z){
    //coordinates
    this->x = x; this->y = y; this->z = z;
}

//draw overload
void cutVoxel::draw(Sculptor &s){
    s.cutVoxel(x, y, z);
}
