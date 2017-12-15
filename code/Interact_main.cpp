// main file to use classes

#include <cmath>
#include "Points.hpp"
#include "Approximation.hpp"

int main(int argc, char* argv[]){

    std::string configfile;
    std::cout<< "What is your file name (it should be located in the directory cmake-build-debug/CMakeFiles/code/CMakefiles): "<<std::endl;

    getline(std::cin, configfile);

    Points points(configfile);
    VectorXd coeff;

    if (points.GetType() == "Approximation"){
        Fitting d(points);
        coeff = d.CalculateCoeff();
        d.printSolution(coeff);
        double err = d.CalculateError(coeff);
    }

    else if (points.GetType() == "Piecewise"){

        PieceWiseInterpolation d(points);

        coeff = d.CalculateCoeff();
        d.printSolution(coeff);
        double err = d.CalculateError(coeff);

    }
    else if ( (points.GetType() == "Polynomial")){
        Interpolation d(points);
        std::cout << "Polynomial " << std::endl;
        coeff = d.CalculateCoeff();
        std::cout << coeff << std::endl;
        d.printSolution(coeff);
    }
    else if (points.GetType() == "PiecewiseContinuous"){
        PieceWiseInterpolation d(points);
        std::cout << "Polynomial " << std::endl;
        coeff = d.CalculateCoeff();
        std::cout << coeff << std::endl;
        d.printSolution(coeff);
        double err = d.CalculateError(coeff);
    }
    return 0;
}

