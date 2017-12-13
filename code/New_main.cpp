// main file to use classes


#include "Testing.h"
#include <cmath>
#include "ReadPointCoord.h"
#include "Points.hpp"
#include "DataFitting.h"
#include "DataInterpolation.h"
#include <string>

double MyFunction(double x){
    return (x/2);
}
int main(int argc, char* argv[]){



  //  std::string config_fileName = argv[1];


   // Testing testing("testing.csv", &MyFunction);

    Config config("config2.csv");
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

    Points points(x,y,n,degree,"type");
    // Approximation

    DataFitting df(points);

    VectorXd coeff = df.CalculateCoeff();

    std::cout << "The solution is:\n" << coeff << std::endl;

    // Piecewise and Polynomial chooses the right one
    DataInterpolation dI(points);

    //VectorXd coeff2 = dI.CalculateCoeff();

    //std::cout << "The solution is:\n" << coeff2 << std::endl;

    // PiecewiseContinuous




    return 0;
    // If type is polynomial verify degree == nPoints-1
        // else, degree given and do piecewise
    //



}

