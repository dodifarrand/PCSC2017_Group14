// main file to use classes

#include <iostream>
#include "ReadPointCoord.h"
#include <Eigen/Dense>
#include "Points.hpp"

int main(int argc, char* argv[]){
    Config config("config.csv");
    std::cout << "File Name: ";
    std::string point_file = config.GetFileName();
    std::cout << point_file.c_str() << std::endl;
    char const* p_file = point_file.c_str();

    int degree;
    std::cout << "degree: ";
    degree = config.GetDegree();
    std::cout << degree << std::endl;

    std::string type = config.GetType();
    std::cout << "type: "<< type.c_str() << std::endl;

    ReadPointCoord readPointCoord(p_file);
    double* x;
    double* y;
    x = readPointCoord.x();
    y = readPointCoord.y();
       int n = readPointCoord.GetNPoints();
    for (int i = 0; i<n; i++){
        std::cout << x[i] << " " << y[i] << std::endl;
    }

   // Points(x,y,n,degree);

    return 0;

}

