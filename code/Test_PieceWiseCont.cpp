/*
 * @file
 * Test_Interpolation.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: Created by Rodolphe
     *  main file to use piecewise interpolation class
 */

#include <cmath>
#include "Points.hpp"
#include "Approximation.hpp"

int main(int argc, char* argv[]){

    Points points("configPiecewiseContinuous.csv");
    VectorXd coeff;

    PieceWiseInterpolation d(points);
    coeff = d.CalculateCoeff();
    d.printSolution(coeff);
    double err = d.CalculateError(coeff);
    return 0;

}