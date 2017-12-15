//
// Created by Anouk Allenspach on 14.12.17.
//
#include "FunctionApprox.h"

// specify your own function

// testing.csv contains: the name of your function (MyOwnFunction), beginning of interval (0), end of interval,
// number of points to generate,type of approximation,degree of approximation

double MyFunction(double x){
    return sin(x/2);
}
int main(int argc, char* argv[]) {
    FunctionApprox fuctionApprox("testing2.csv", &MyFunction);

    return 0;

}