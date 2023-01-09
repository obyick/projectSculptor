#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

#include "sculptor.h"
#include "voxel.h"

//constructor
Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;
    r = g = b = a = 0;

    //dinamic allocation of x
    v = new Voxel**[nx];

    //dinamic allocation of y
    for(int i = 0; i < nx; i++) v[i] = new Voxel*[ny];

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

//destructor
Sculptor::~Sculptor(){
    //memory release of z
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++) delete[] v[i][j];
    }

    //memory release of y
    for(int i = 0; i < nx; i++) delete[] v[i];

    //memory release of x
    delete[] v;

    //returning dimension to 0
    nx = ny = nz = 0;
}

//set collors 0 to 1
void Sculptor::setColor(float _r, float _g, float _b, float _a){
    r = _r;
    g = _g;
    b = _b;
    a = _a;
}

//create voxel
void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = r;
    v[x][y][z].g = g;
    v[x][y][z].b = b;
    v[x][y][z].a = a;
}

//disable voxel
void Sculptor::cutVoxel(int x, int y, int z){v[x][y][z].isOn = false;}

//create box
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k < z1; k++) Sculptor::putVoxel(i, j, k);
        }
    }
}

//disable box
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k < z1; k++) Sculptor::cutVoxel(i, j, k);
        }
    }
}

//create sphere
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int i = 0; i < xcenter + radius; i++){
        for(int j = 0; j < ycenter + radius; j++){
            for(int k = 0; k < zcenter + radius; k++){
                if((pow(i - xcenter, 2) + pow(j - ycenter, 2) + pow(k - zcenter, 2)) < pow(radius, 2)){
                    Sculptor::putVoxel(i, j, k);
                }
            }
        }
    }
}

//disable sphere
void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int i = 0; i < xcenter + radius; i++){
        for(int j = 0; j < ycenter + radius; j++){
            for(int k = 0; k < zcenter + radius; k++){
                if((pow(i - xcenter, 2) + pow(j - ycenter, 2) + pow(k - zcenter, 2)) < pow(radius, 2)){
                    Sculptor::cutVoxel(i, j, k);
                }
            }
        }
    }
}

//create ellipsoid
void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int i = 0; i < xcenter + rx; i++){
        for(int j = 0; j < ycenter + ry; j++){
            for(int k = 0; k < zcenter + rz; k++){
                if((pow(i - xcenter, 2) / pow(rx, 2)) + (pow(j - ycenter, 2) / pow(ry, 2)) + (pow(k - zcenter, 2) / pow(rz, 2)) < 1){
                    Sculptor::putVoxel(i, j, k);
                }
            }
        }
    }
}

//disable ellipsoid
void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int i = 0; i < xcenter + rx; i++){
        for(int j = 0; j < ycenter + ry; j++){
            for(int k = 0; k < zcenter + rz; k++){
                if((pow(i - xcenter, 2) / pow(rx, 2)) + (pow(j - ycenter, 2) / pow(ry, 2)) + (pow(k - zcenter, 2) / pow(rz, 2)) < 1){
                    Sculptor::cutVoxel(i, j, k);
                }
            }
        }
    }
}

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

    //output file type
    fileOut << "OFF" << std::endl;

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

    //output dimensions values
    fileOut << vertices << " " << faces << " " << 0 << std::endl;

    //structure of faces
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

    //define colors and transparency
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

    //save file
    if(fileOut.is_open()) std::cout << ".off was saved" << std::endl;

    //exit file
    fileOut.close();
}
