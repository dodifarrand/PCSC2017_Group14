// main file to use classes


#include "FuctionApprox.h"
#include <cmath>
#include "ReadPointCoord.h"
#include "Points.hpp"
#include "DataFitting.h"
#include "DataInterpolation.h"
#include <string>

#include "Solution.h"
double MyFunction(double x){
    return (x/2);
}
int main(int argc, char* argv[]){



  //  std::string config_fileName = argv[1];


   // Testing testing("testing.csv", &MyFunction);

    Config config("config2.csv");
    std::cout << "File Name of your configuration file : ";
    std::string point_file = config.GetFileName();
    //std::cout << point_file.c_str() << std::endl;
    char const* p_file = point_file.c_str();

    int degree;
    std::cout << "you have selected degree: ";
    degree = config.GetDegree();
    std::cout << degree << std::endl;

    std::string type = config.GetType();
    std::cout << "let's do a(n) "<< type.c_str() << " with the points in your file " << point_file <<std::endl;

    ReadPointCoord readPointCoord(p_file);
    double* x;
    double* y;
    x = readPointCoord.x();
    y = readPointCoord.y();
    int n = readPointCoord.GetNPoints();
    for (int i = 0; i<n; i++){
//        std::cout << x[i] << " " << y[i] << std::endl;
    }

    Points points(x,y,n,degree);
    VectorXd coeff;

    if (type == "Approximation"){
        DataFitting df(points);

        coeff = df.CalculateCoeff();


    }

    else if ((type == "Piecewise") || (type == "Polynomial")){

        DataInterpolation dI(points);

        coeff = dI.CalculateCoeff();

    }
    else if (type == "PiecewiseContinuous"){

    }

    Solution(coeff, degree);

    return 0;
    // If type is polynomial verify degree == nPoints-1
        // else, degree given and do piecewise
    //



}

