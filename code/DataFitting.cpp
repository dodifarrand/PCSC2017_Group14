//
// Created by Anouk Allenspach on 13.12.17.
//

#include "DataFitting.h"

/**
* This is our DataFitting Class
*/


// exactly the same code as in Approx class!
VectorXd DataFitting::CalculateCoeff() {

    // vectors storing what will go into matrix
    double val [2*degree+1];
    double val2 [degree+1];

    // matrix A and vector b (Ax=b)
    MatrixXd A(degree+1,degree+1);
    VectorXd b(degree+1);

    // fill vector that will be A (val) and b (val2)
    for(int n = 0; n<2*degree+1;n++) {
        val[n] = 0;
        if(n<degree+1){
            val2[n] = 0;
        }
    }
    for(int n = 0; n<2*degree+1;n++){
        for(int i = 0; i<nbPoint;i++){
            val[n]+=pow(x[i],2*degree-n);
            if(n<degree+1){
                val2[n] += pow(x[i],degree-n)*y[i];
            }
        }
    }
    // put values in matrix A and vector b
    for(int i = 0; i<degree+1;i++){
        for(int j = 0; j<degree+1;j++){
            int n = i+j;
            A(i,j)=val[n];
        }
        b(i)=val2[i];
    }
    std::cout << "Here is the matrix A:\n" << A << std::endl;
    std::cout << "Here is the vector b:\n" << b << std::endl;
    // solve Ax = b
    VectorXd a = A.fullPivLu().solve(b);

    // free memory

    // return solution
    return a;
}


// method to compute error of approximation
double DataFitting::CalculateError(VectorXd a) {
    // initialize err and pointer to double fx
    double err = 0;
    double *fx = new double[nbPoint];

    // compute fx
    for(int i = 0; i<nbPoint;i++){
        fx[i] = 0;
        for(int j = 0; j<degree+1;j++){
            fx[i] += pow(x[i],degree-j)*a(j);   // a(j) is the coeff  for x^(degree-j), x[i] is the x coordinate of point i
        }
        err += pow(y[i]-fx[i],2);   // increment error
    }

    // free memory
    delete[] fx;

    // return the error
    return err;
}
