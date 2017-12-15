
/*
 * @file
 * TestEmptyConfig.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: Created by Anouk Allenspach
     *  test empty config file
 */


#include <cmath>
#include "Points.hpp"
#include "Approximation.hpp"

int main(int argc, char* argv[]){

    Points points("configEmpty.csv");
    VectorXd coeff;

    Fitting d(points);
    coeff = d.CalculateCoeff();
    d.printSolution(coeff);
    double err = d.CalculateError(coeff);
    return 0;

}