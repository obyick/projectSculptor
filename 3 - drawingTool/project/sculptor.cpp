#include "sculptor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cstdlib>
#include <iomanip>

using namespace std;

Sculptor::Sculptor(int nx_, int ny_, int nz_){
    nx = nx_;
    ny = ny_;
    nz = nz_;
    v = new Voxel**[nx];

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

//set collors 0 to 255
void Sculptor::setColor(float r, float g, float b){
    this -> r = r;
    this -> g = g;
    this -> b = b;
}

//create voxel
void Sculptor::putVoxel(int x, int y, int z){
    if(x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz){
        v[x][y][z].isOn = true;
        v[x][y][z].r = r;
        v[x][y][z].g = g;
        v[x][y][z].b = b;
    }
}

//disable voxel
void Sculptor::cutVoxel(int x, int y, int z){
    if(x >= 0 && x < nx && y >= 0 && y < ny && z >= 0 && z < nz){
        v[x][y][z].isOn = false;
    }
}

//create box
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k < z1; k++) putVoxel(i, j, k);
        }
    }
}

//disable box
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = x0; i < x1; i++){
        for(int j = y0; j < y1; j++){
            for(int k = z0; k < z1; k++) cutVoxel(i, j, k);
        }
    }
}

//create sphere
void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int i = 0; i < xcenter + radius; i++){
        for(int j = 0; j < ycenter + radius; j++){
            for(int k = 0; k < zcenter + radius; k++){
                if((pow(i - xcenter, 2) + pow(j - ycenter, 2) + pow(k - zcenter, 2)) < pow(radius, 2)){
                    putVoxel(i, j, k);
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
                    cutVoxel(i, j, k);
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
                    putVoxel(i, j, k);
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
                    cutVoxel(i, j, k);
                }
            }
        }
    }
}

//create file .off
void Sculptor::writeOFF(string filename){
    ofstream fileOut; //flux output
    fixed(fileOut);       //set point notations
    fileOut << setprecision(2);

    //Variables and values
    int vertices = 0;
    int faces    = 0;
    int aux      = 0;

    //Opening file
    fileOut.open(filename);
    if(fileOut.is_open() == false){
        cout << "Try open the file again!" << endl;
        exit(1);
    }

    //Output file type
    fileOut << "OFF" << endl;

    //Define cube dimensions, if isOn equal true
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

    //Output dimensions values
    fileOut << vertices << " " << faces << " " << 0 << endl;

    //Structure of faces
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if(v[i][j][k].isOn){
                    fileOut << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    fileOut << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    fileOut << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    fileOut << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    fileOut << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                    fileOut << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    fileOut << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    fileOut << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                }
            }
        }
    }

    //Define colors
    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if(v[i][j][k].isOn){
                    fileOut << 4 << " " << aux + 0 << " " << aux + 3 << " " << aux + 2 << " " << aux + 1 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << endl;
                    fileOut << 4 << " " << aux + 4 << " " << aux + 5 << " " << aux + 6 << " " << aux + 7 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << endl;
                    fileOut << 4 << " " << aux + 0 << " " << aux + 1 << " " << aux + 5 << " " << aux + 4 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << endl;
                    fileOut << 4 << " " << aux + 0 << " " << aux + 4 << " " << aux + 7 << " " << aux + 3 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << endl;
                    fileOut << 4 << " " << aux + 3 << " " << aux + 7 << " " << aux + 6 << " " << aux + 2 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << endl;
                    fileOut << 4 << " " << aux + 1 << " " << aux + 2 << " " << aux + 6 << " " << aux + 5 << " " <<
                               v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << endl;
                    aux += 8;
                }
            }
        }
    }

    //Save and exit file
    if(fileOut.is_open()) cout << ".off was saved" << endl;
    fileOut.close();
}

vector<vector<Voxel>> Sculptor::getPlano(int i, int plano){
    vector<vector<Voxel>> re;
    vector<Voxel> line;
    if(plano == XY){
        line.resize(ny);
        for(int j = 0; j < nx; j++){
            for(int k = 0; k < ny; k++){
                line[k].r = v[j][k][i].r;
                line[k].g = v[j][k][i].g;
                line[k].b = v[j][k][i].b;
                line[k].isOn = v[j][k][i].isOn;
            }
            re.push_back(line);
        }
    }

    return re;
}
