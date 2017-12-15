/*
 * @file
 * Test_Fitting.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: Created by Rodolphe
     *  main file to use data fitting
 *///

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

