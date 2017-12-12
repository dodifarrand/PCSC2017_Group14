// main file to use classes


#include "Testing.h"
#include <cmath>
#include "ReadPointCoord.h"
double MyFunction(double x){
    return (x/2);
}
int main(int argc, char* argv[]){

    Testing testing("testing.csv", &MyFunction);

    Config config("config2.csv");
    std::cout << "File Name: ";
    std::string point_file = config.GetFileName();
    std::cout << point_file.c_str() << std::endl;
    char const* p_file = point_file.c_str();

    int degree;
    std::cout << "degree: ";
    degree = config.GetDegree();
    std::cout << degree << std::endl;

    std::string type = config.GetType();
    std::cout << "type: "<< type.c_str() << std::endl;

    ReadPointCoord readPointCoord(p_file);
    double* x;
    double* y;
    x = readPointCoord.x();
    y = readPointCoord.y();
    int n = readPointCoord.GetNPoints();
    for (int i = 0; i<n; i++){
        std::cout << x[i] << " " << y[i] << std::endl;
    }
    return 0;

}

