#ifndef CUTSPHERE_H
#define CUTSPHERE_H

#include "geometricFigure.h"

class cutSphere : public geometricFigure{
public:
    int x, y, z, radius; //tridimensional coordinates
    cutSphere(int x, int y, int z, int radius);
    void draw(Sculptor &s);
};

#endif // CUTSPHERE_H
