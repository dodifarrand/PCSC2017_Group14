#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <math.h>
#include "Points.hpp"
#include "Approximation.hpp"
using namespace std;
using namespace Eigen;
using std::vector;

vector<double> linspace(double a, double b, int n);

int main() {
    double *xi = new double[9];
    double *yi = new double[9];
    double *funci = new double[41];
    vector<double> vec = linspace(-10,10,41);
    for(int i = 0;i<41;i++){
        funci[i]=0.003*pow(vec[i],6)-6*pow(vec[i],4)-3;
    }
    int j = 0;
    for(int i = 0;i<41;i+=5){
        xi[j]=vec[i];
        yi[j]=funci[i];
        j = j+1;
    }
    int pointsNb = 9;
    int degree = 3;
    Points P(xi,yi,pointsNb,degree);
    Approximation A(P);
    VectorXd coeff = A.CalculateCoeff();
    cout << "The solution is:\n" << coeff << endl;


}

VectorXd Approximation::CalculateCoeff() {
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
    cout << "Here is the matrix A:\n" << A << endl;
    cout << "Here is the vector b:\n" << b << endl;
    return a;
}

vector<double> linspace(double a, double b, int n) {
    vector<double> array;
    double step = (b-a) / (n-1);

    while(a <= b) {
        array.push_back(a);
        a += step;           // could recode to better handle rounding errors
    }
    return array;
}
