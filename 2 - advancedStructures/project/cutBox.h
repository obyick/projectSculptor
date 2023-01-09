#ifndef CUTBOX_H
#define CUTBOX_H

#include "geometricFigure.h"

class cutBox : public geometricFigure{
public:
    int x0, x1, y0, y1, z0, z1; //tridimensional coordinates
    cutBox(int x0, int x1, int y0, int y1, int z0, int z1);
    void draw(Sculptor &s);
};

#endif // CUTBOX_H
