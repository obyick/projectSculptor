#ifndef GEOMETRICFIGURE_H
#define GEOMETRICFIGURE_H

#include "sculptor.h"

class geometricFigure{
protected:
    float r, g, b, a; //current drawing color
public:
    geometricFigure();
    virtual ~geometricFigure();
    virtual void draw(Sculptor &s) = 0;
};

#endif // GEOMETRICFIGURE_H
