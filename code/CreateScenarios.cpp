/*
 * @file
 * CreateScenarios.cpp
 *
 *  Created on: Dec 14, 2017
 *      Author: Created by Anouk Allenspach
     *  implementation of CreateScenrios class
 */

#include "FunctionApprox.h"

// testing.csv contains: the name of your function (MyOwnFunction), beginning of interval (0), end of interval,
// number of points to generate,type of approximation,degree of approximation

// example functions
double MyComplicatedFunction(double x){
    return exp(x/2)-pow(x,3);
}

double MyCosSinFunction(double x){
    return cos(x)*sin(x/2);
}

double MySinFunction(double x){
    return sin(x/2);
}

double MyIntFunction(double x){
    return log(x)-x;
}


int main(int argc, char* argv[]) {
   // FunctionApprox fuctionApprox("testing4.csv", &MyComplicatedFunction);   // PiecewiseContinuous
    FunctionApprox fuctionApprox1("testing3.csv", &MyCosSinFunction);       // Piecewise
   // FunctionApprox fuctionApprox2("testing2.csv", &MySinFunction);          // Fitting
   // FunctionApprox fuctionApprox3("testing1.csv", &MyIntFunction);          // Interpolation

    return 0;

}