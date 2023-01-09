#ifndef PUTSPHERE_H
#define PUTSPHERE_H

#include "sculptor.h"
#include "geometricFigure.h"

class putSphere : public geometricFigure{
public:
    int x, y, z, radius; //tridimensional coordinates
    float r, g, b, a; //color and transparency

    //method constructor
    putSphere(int x, int y, int z, int radius,
              float r, float g, float b, float a);
    ~putSphere(); //method destructor
    void draw(Sculptor &s); //draw overload
};

#endif // PUTSPHERE_H
