#ifndef CUTVOXEL_H
#define CUTVOXEL_H

#include "geometricFigure.h"

class cutVoxel : public geometricFigure{
public:
    int x, y, z; //tridimensional coordinates
    cutVoxel(int x, int y, int z);
    void draw(Sculptor &s);
};

#endif // CUTVOXEL_H
