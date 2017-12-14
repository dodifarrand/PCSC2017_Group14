//
// Created by Anouk Allenspach on 14.12.17.
//

#include "Solution.h"
Solution::Solution(VectorXd coeff, int degree){
std::cout << "The solution is: f(x) = " << std::setprecision(5) << std::fixed;

double tol = .1e-4;
for (int i = 0; i< degree-1 ; i++){
int power = degree -i;
std::cout   << coeff[i] << " * x^" << power;

if (coeff[i+1] > tol ){
std::cout << " + ";
}
else if (coeff[i+1] <= tol ){
std::cout << " ";
}
}
std::string sign = "";

if (coeff[degree+1]<=tol){
sign = " + ";
}
std::cout  << coeff[degree] << " x " << sign << coeff[degree+1] << std::endl;
}