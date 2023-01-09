#ifndef PUTVOXEL_H
#define PUTVOXEL_H

#include "sculptor.h"
#include "geometricFigure.h"

class putVoxel : public geometricFigure{
public:
    int x, y, z; //tridimensional coordinates
    float r, g, b, a; //color and transparency

    //method constructor
    putVoxel(int x, int y, int z,
             float r, float g, float b, float a);
    ~putVoxel(); //method destructor
    void draw(Sculptor &s); //draw overload
};

#endif // PUTVOXEL_H
