#ifndef PUTBOX_H
#define PUTBOX_H

#include "sculptor.h"
#include "geometricFigure.h"

class putBox : public geometricFigure{
public:
    int x0, x1, y0, y1, z0, z1; //tridimensional coordinates
    float r, g, b, a; //color and transparency

    //method constructor
    putBox(int x0, int x1, int y0, int y1, int z0, int z1,
           float r, float g, float b, float a);
    ~putBox(); //method destructor
    void draw(Sculptor &s); //draw overload
};

#endif // PUTBOX_H
