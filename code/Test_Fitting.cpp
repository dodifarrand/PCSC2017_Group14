// main file to use classes

#include <cmath>
#include "Points.hpp"
#include "Approximation.hpp"

int main(int argc, char* argv[]){

    Points points("configFitting.csv");
    VectorXd coeff;

    Fitting d(points);
    coeff = d.CalculateCoeff();
    d.printSolution(coeff);
    double err = d.CalculateError(coeff);
    return 0;

}

