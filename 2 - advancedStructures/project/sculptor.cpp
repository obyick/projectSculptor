#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

#include "sculptor.h"
#include "voxel.h"

//method constructor
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;
    r = g = b = a = 0;

    v = new Voxel**[nx]; //dinamic allocation of x

    for(int i = 0; i < nx; i++) v[i] = new Voxel*[ny]; //dinamic allocation of y

    //dinamic allocation of z
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++) v[i][j] = new Voxel[nz];
    }

    //disable all voxels
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++) v[i][j][k].isOn = false;
        }
    }
}

//method destructor
Sculptor::~Sculptor(){
    //memory release of z
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++) delete[] v[i][j];
    }

    for(int i = 0; i < nx; i++) delete[] v[i]; //memory release of y

    delete[] v; //memory release of x

    nx = ny = nz = 0; //returning dimension to 0
}

//set collors 0 to 1
void Sculptor::setColor(float r, float g, float b, float a){
    this -> r = r;
    this -> g = g;
    this -> b = b;
    this -> a = a;
}

//create voxel
void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

void Sculptor::cutVoxel(int x, int y, int z){v[x][y][z].isOn = false;} //disable voxel

//create file .off
void Sculptor::writeOFF(const char* filename){
    std::ofstream fileOut; //flux output
    fixed(fileOut); //set point notations
    fileOut << std::setprecision(2);

    //variables and values
    int vertices = 0;
    int faces    = 0;
    int aux      = 0;

    //opening file
    fileOut.open(filename);
    if(fileOut.is_open() == false){
        std::cout << "Try open the file again!" << std::endl;
        exit(1);
    }

    fileOut << "OFF" << std::endl; //output file type

    //define cube dimensions, if isOn equal true
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if(v[i][j][k].isOn){
                    vertices += 8;
                    faces += 6;
                }
            }
        }
    }

    fileOut << vertices << " " << faces << " " << 0 << std::endl;//output dimensions values

    //Structure of faces
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if(v[i][j][k].isOn){
                    fileOut << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    fileOut << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    fileOut << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << std::endl;
                    fileOut << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << std::endl;
                    fileOut << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                    fileOut << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    fileOut << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << std::endl;
                    fileOut << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << std::endl;
                }
            }
        }
    }

    //Define colors and transparency
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if(v[i][j][k].isOn){
                    fileOut << 4 << " " << aux + 0 << " " << aux + 3 << " " << aux + 2 << " " << aux + 1 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fileOut << 4 << " " << aux + 4 << " " << aux + 5 << " " << aux + 6 << " " << aux + 7 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fileOut << 4 << " " << aux + 0 << " " << aux + 1 << " " << aux + 5 << " " << aux + 4 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fileOut << 4 << " " << aux + 0 << " " << aux + 4 << " " << aux + 7 << " " << aux + 3 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fileOut << 4 << " " << aux + 3 << " " << aux + 7 << " " << aux + 6 << " " << aux + 2 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    fileOut << 4 << " " << aux + 1 << " " << aux + 2 << " " << aux + 6 << " " << aux + 5 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << std::endl;
                    aux += 8;
                }
            }
        }
    }

    //Save and exit the file
    if(fileOut.is_open()) std::cout << ".off was saved" << std::endl;
    fileOut.close();
}
