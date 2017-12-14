// main file to use classes


#include "FuctionApprox.h"
#include <cmath>
#include "Config.h"
#include "Points.hpp"
#include "Approximation.hpp"
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

    //ReadPointCoord points1(p_file);
    Points points(p_file);

    std::cout << "created point object" << std::endl;
    int n = points.GetNPoints();
    std::cout << "Number of points " <<  n << std::endl;

    VectorXd coeff;

    if (type == "Approximation"){
        Fitting d(points);

        coeff = d.CalculateCoeff();
        d.printSolution(coeff);


    }

    else if ((type == "Piecewise") || (type == "Polynomial")){

        Interpolation d(points);

        coeff = d.CalculateCoeff();
        d.printSolution(coeff);

    }
    else if (type == "PiecewiseContinuous"){

    }




    return 0;




}

