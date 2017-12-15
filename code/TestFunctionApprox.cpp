
/**
 * @file
 * TestFunctionApprox.cpp
 *
 *  Created on: Dec 15, 2017
 *      Author: Created by Anouk Allenspach
 *      class to read the configuration file named config.csv
 */

#include "FunctionApprox.h"

// specify your own function

// first generate a .csv file named testing
// testing.csv contains: the name of your function (MyOwnFunction), beginning of interval (0), end of interval,
// number of points to generate,type of approximation,degree of approximation

double MyOwnFunction(double x){
    return exp(x/2)-pow(x,3);
}


int main(int argc, char* argv[]) {
    FunctionApprox fuctionApprox1("testing.csv", &MyOwnFunction);


    return 0;

}