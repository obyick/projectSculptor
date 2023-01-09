#ifndef PUTELLIPSOID_H
#define PUTELLIPSOID_H

#include "sculptor.h"
#include "geometricFigure.h"

class putEllipsoid : public geometricFigure{
public:
    int xcenter, ycenter, zcenter, rx, ry, rz; //tridimensional coordinates
    float r, g, b, a; //color and transparency

    //method constructor
    putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz,
                 float r, float g, float b, float a);
    ~putEllipsoid(); //method destructor
    void draw(Sculptor &s); //draw overload
};

#endif // PUTELLIPSOID_H
