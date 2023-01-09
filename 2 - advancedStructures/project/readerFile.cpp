#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>

#include "readerFile.h"
#include "putVoxel.h"
#include "cutVoxel.h"
#include "putBox.h"
#include "cutBox.h"
#include "putSphere.h"
#include "cutSphere.h"
#include "putEllipsoid.h"
#include "cutEllipsoid.h"

readerFile::readerFile(){} //method constructor
readerFile::~readerFile(){} //method destructor

// method to read an input file
std::vector<geometricFigure*> readerFile::parse(std::string filename){
    std::vector <geometricFigure*> figure; //vector to walk element to element
    std::fstream fileIn; //flux input
    std::string aux; //auxiliare string

    fileIn.open(filename); //Opening file

    //verify if the fileIn is open
    if(fileIn.is_open() == false){
        std::cout << "Try open the file again!" << std::endl;
        exit(EXIT_FAILURE);
    }

    //verify if the flux input is ready to read
    while(fileIn.good()){
        //read all lines and break if not
        fileIn >> aux;
        if(!fileIn.good()) break;

        //first line
        if(aux.compare("dim") == 0){
            fileIn >> x >> y >> z;
        }

        //putVoxel method compare strings to init the input flux
        else if(aux.compare("putVoxel") == 0){
            int x, y, z;
            fileIn >> x >> y >> z >> r >> g >> b >> a;
            figure.push_back(new putVoxel(x, y, z, r, g, b, a));
        }

        //cutVoxel method compare strings to init the input flux
        else if(aux.compare("cutVoxel") == 0){
            int x, y, z;
            fileIn >> x >> y >> z;
            figure.push_back(new cutVoxel(x, y, z));
        }

        //putBox method compare strings to init the input flux
        else if(aux.compare("putBox") == 0){
            int x0, x1, y0, y1, z0, z1;
            fileIn >> x0 >> x1 >> y0 >> y1 >> z0 >> z1 >> r >> g >> b >> a;
            figure.push_back(new putBox(x0, x1, y0, y1, z0, z1, r, g, b, a));
        }
        //cutBox method compare strings to init the input flux
        else if(aux.compare("cutBox") == 0){
            int x0, x1, y0, y1, z0, z1;
            fileIn >> x0 >> x1 >> y0 >> y1 >> z0 >> z1;
            figure.push_back(new cutBox(x0, x1, y0, y1, z0, z1));
        }

        //putSphere method compare strings to init the input flux
        else if(aux.compare("putSphere") == 0){
            int x, y, z, radius;
            fileIn >> x >> y >> z >> radius >> r >> g >> b >> a;
            figure.push_back(new putSphere(x, y, z, radius, r, g, b, a));
        }

        //cutSphere method compare strings to init the input flux
        else if(aux.compare("cutSphere") == 0){
            int x, y, z, radius;
            fileIn >> x >> y >> z >> radius;
            figure.push_back(new cutSphere(x, y, z, radius));
        }

        //putEllipsoid method compare strings to init the input flux
        else if(aux.compare("putEllipsoid") == 0){
            int xcenter, ycenter, zcenter, rx, ry, rz;
            fileIn >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz >> r >> g >> b >> a;
            figure.push_back(new putEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz, r, g, b, a));
        }

        //cutEllipsoid method compare strings to init the input flux
        else if(aux.compare("cutEllipsoid") == 0){
            int xcenter, ycenter, zcenter, rx, ry, rz;
            fileIn >> xcenter >> ycenter >> zcenter >> rx >> ry >> rz;
            figure.push_back(new cutEllipsoid(xcenter, ycenter, zcenter, rx, ry, rz));
        }
    }

    //show feedback, exit file and return vector figure
    if(fileIn.is_open()) std::cout << ".txt was read" << std::endl;
    fileIn.close();
    return figure;
}

//dimensional methods
int readerFile::getx(){return x;}
int readerFile::gety(){return y;}
int readerFile::getz(){return z;}
