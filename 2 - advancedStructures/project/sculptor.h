#ifndef SCULPTOR_H
#define SCULPTOR_H

#include "voxel.h"

class Sculptor{
private:
    Voxel ***v;  //3D matrix
    int nx, ny, nz; //dimensions
    float r, g, b, a; //current drawing color
public:
    Sculptor(int _nx, int _ny, int _nz); //method constructor
    ~Sculptor(); //method destructor
    void setColor(float r, float g, float b, float a); //method to set colors and transparency
    void putVoxel(int x, int y, int z); //method to create a voxel
    void cutVoxel(int x, int y, int z); //method to delete a voxel
    void writeOFF(const char* filename); //method to create file type .OFF
};

#endif // SCULPTOR_H
