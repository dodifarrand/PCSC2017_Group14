#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>
#include <cassert>

void myFunc1(){

}

int main(int argc, char* argv[]){


// ******************************************************************************************************
    // Enter a function
    std::cout << "Enter function you would like to approximate and press enter\n";
    std::string func_name;
    std::getline(std::cin, func_name);

    std::string plus ("+");
    std::string minus ("-");
    std::string mult ("*");
    std::string division ("/");

    // different member versions of find in the same order as above:
    std::size_t found_plus = func_name.find(plus);
    std::size_t found_minus = func_name.find(minus);
    std::size_t found_mult = func_name.find(mult);
    std::size_t found_division = func_name.find(division);
    // trigonometric expressions
    std::size_t found_sin = func_name.find("sin");
    std::size_t found_exp = func_name.find("exp");
    std::size_t found_log = func_name.find("log");

    // expression in brackets
    std::size_t found_openbrackets = func_name.find("(");
    std::size_t found_closebrackets = func_name.find(")");



    std::size_t found_x = func_name.find("x");

    int n_plus= std::count( func_name.begin(), func_name.end(), '+' );
    int n_minus= std::count( func_name.begin(), func_name.end(), '-' );
    int n_mults = std::count( func_name.begin(), func_name.end(), '*' );
    int n_div= std::count( func_name.begin(), func_name.end(), '/' );
    int n_x = std::count( func_name.begin(), func_name.end(), 'x' );
    int n_sin = std::count( func_name.begin(), func_name.end(), 'sin(' );
    int n_exp = std::count( func_name.begin(), func_name.end(), 'exp(' );
    int n_log = std::count( func_name.begin(), func_name.end(), 'log(' );


    // priority
    if (found_exp!=std::string::npos){
        for (int i = 0; i < n_exp; i++){

        }
    }
    else if (found_exp==std::string::npos){

    }



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
