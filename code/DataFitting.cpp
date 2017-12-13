//
// Created by Anouk Allenspach on 13.12.17.
//

#include "DataFitting.h"


VectorXd DataFitting::CalculateCoeff() {
    double *val = new double[2*degree+1];
    double *val2 = new double[degree+1];
    MatrixXd A(degree+1,degree+1);
    VectorXd b(degree+1);
    for(int n = 0; n<=2*degree;n++){
        val[n]=0;
        val2[n]=0;
        for(int i = 0; i<nbPoint;i++){
            val[n]+=pow(x[i],2*degree-n);
            if(n<degree+1){
                val2[n] += pow(x[i],degree-n)*y[i];
            }
        }
    }
    for(int i = 0; i<degree+1;i++){
        for(int j = 0; j<degree+1;j++){
            A(i,j)=val[i+j];
        }
        b(i)=val2[i];
    }
    VectorXd a = A.colPivHouseholderQr().solve(b);
    delete[] val;
    delete[] val2;
    return a;
}

double DataFitting::CalculateError(VectorXd a) {
    double err = 0;
    double *fx = new double[nbPoint];
    for(int i = 0; i<nbPoint;i++){
        fx[i] = 0;
        for(int j = 0; j<degree+1;j++){
            fx[i] += pow(x[i],degree-j)*a(j);
        }
        err += pow(y[i]-fx[i],2);
    }
    delete[] fx;
    return err;
}
