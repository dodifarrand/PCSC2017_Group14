// main file to use classes

#include <iostream>
#include "ReadPointCoord.h"


int main(int argc, char* argv[]) {


    ReadPointCoord readPoints;
    readPoints.ReadData();
    double* x;
    double* y;
    x = readPoints.x();
    y = readPoints.y();
    int n = readPoints.GetNLines();
    for (int i = 0; i<n; i++){
        std::cout << x[i] << " " << y[i] << std::endl;
    }


    return 0;

}

