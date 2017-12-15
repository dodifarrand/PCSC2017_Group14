#include <cmath>
#include "Points.hpp"
#include "Approximation.hpp"

int main(int argc, char* argv[]){

    Points points("configInterpolation.csv");
    VectorXd coeff;

    Interpolation d(points);
    coeff = d.CalculateCoeff();
    d.printSolution(coeff);
    double err = d.CalculateError(coeff);
    return 0;

}