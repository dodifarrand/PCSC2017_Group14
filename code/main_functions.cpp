#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <cassert>

int main(int argc, char* argv[]){


// ******************************************************************************************************
    // Enter a function
    std::cout << "Enter  function you would like to approximate and press enter\n";
    std::string func_name;
    std::getline(std::cin, func_name);


    // end of read file
    int n; // degree of polynomial
    std::cout << "Enter degree of polynomial do you want to use?" << std::endl;
    // add assert statement of check for validity
    std::cin >> n;


    std::cout << "Enter the beginning of the interval"  << std::endl;
    int a;
    std::cin >> a;
    int b;
    std::cout << "Enter the end of the interval"  << std::endl;
    std::cin >> b;
    std::cout << "How many data points should be generated in the interval [" << a <<", " << b << "] ?\n";
    int N; // number of data pairs
    std::cin >> N;
    assert(N>n);
// ******************************************************************************************************
    // write to output file
    double steps = double((b-a))/(N-1);
  //  std::cout << steps << std::endl;
    double x[N], y[N];
   // std::cout << sin(a) << std::endl;
   // std::cout << sin(b) << std::endl;
    double (*p_function)(double x);

// simple functions
    if (func_name=="sin(x)"){
        p_function = &sin;
    }
    else if (func_name=="cos(x)"){
        p_function = &cos;
    }
    else if (func_name=="tan(x)"){
        p_function = &tan;
    }
    else if (func_name=="exp(x)"){
        p_function = &exp;
    }
    else if (func_name=="log(x)"){
        p_function = &log;
    }


    for (int i = 0; i < N; i++){
        x[i] = a+i*steps;
        std::cout << x[i] << std::endl;
        y[i] = p_function(a+double(i)*steps);
        std::cout << y[i] << std::endl;

    }


// could also ask user to specify file name
    std::ofstream write_output(func_name+".csv");
    assert(write_output.is_open());
    for (int i = 0; i < N-1; i++){
        write_output << x[i] << "," << y[i] << std::endl;

    }
    write_output << x[N-1] << "," << y[N-1];
// ******************************************************************************************************
    write_output.close();

// ******************************************************************************************************
    // Enter a function


    // now we have the points and the number of lines to read from file
    return 0;

}
