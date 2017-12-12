// main file to use classes


#include "Testing.h"
#include <cmath>

double MyFunction(double x){
    return (x/2);
}
int main(int argc, char* argv[]){

    Testing testing("testing.csv", &MyFunction);

    return 0;

}

