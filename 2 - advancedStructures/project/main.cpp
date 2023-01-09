#include <iostream>
#include <vector>

#include "geometricFigure.h"
#include "readerFile.h"
#include "sculptor.h"

int main(){
    Sculptor *s;

    readerFile prsr;

    std::vector<geometricFigure*> figure;
    figure = prsr.parse("C:/Users/mathe/us/Projects/Qt/projectSculptor/2 - advancedStructures/Barad-Dur.txt");

    s = new Sculptor(prsr.getx(), prsr.gety(), prsr.getz());

    for(int i = 0; i < int(figure.size()); i++) figure[i] -> draw(*s);

    s -> writeOFF("Barad-Dur.off");

    for(int i = 0; i < int(figure.size()); i++) delete figure[i];
    delete s;

    return 0;
}
