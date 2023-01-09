#ifndef READERFILE_H
#define READERFILE_H

#include <vector>
#include <string>

#include "geometricFigure.h"

class readerFile{
public:
    int x, y, z;
    float r, g, b, a;
    readerFile();
    ~readerFile();
    std::vector <geometricFigure*> parse(std::string filename);
    int getx();
    int gety();
    int getz();
};

#endif // READERFILE_H
