#ifndef CUTELLIPSOID_H
#define CUTELLIPSOID_H

#include "geometricFigure.h"

class cutEllipsoid : public geometricFigure{
public:
    int xcenter, ycenter, zcenter, rx, ry, rz; //tridimensional coordinates
    cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz);
    void draw(Sculptor &s);
};

#endif // CUTELLIPSOID_H
