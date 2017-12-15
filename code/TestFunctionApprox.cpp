/**
 * @file
 * TestFunctionApprox.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: Created by Anouk Allenspach
 *      main file demonstrating how to generate a config file and the associated points for a function (MyOwnFunction)
 *      implemented by the user
 */

#include "FunctionApprox.h"


// first generate a .csv file named testing
// testing.csv contains: the name of your function (MyOwnFunction), beginning of interval (0), end of interval,
// number of points to generate,type of approximation,degree of approximation

// specify your own function here, replacing x with your function f(x)
double MyOwnFunction(double x){
    return x;
}


int main(int argc, char* argv[]) {
    FunctionApprox fuctionApprox1("testing.csv", &MyOwnFunction);

    return 0;

}