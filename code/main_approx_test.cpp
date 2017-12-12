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
    DataFitting df(P);
    DataInterpolation di(P);
    VectorXd coeff1 = A.CalculateCoeff();
    VectorXd coeff2 = df.CalculateCoeff();
    VectorXd coeff3 = di.CalculateCoeff();
    double error = df.CalculateError(coeff1);
    cout << "The solution is:\n" << coeff1 << endl;
    cout << "The solution is:\n" << coeff2 << endl;
    cout << "The solution is:\n" << coeff3 << endl;
    cout << "The error is: \n" << error <<endl;


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
    return a;
}

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

VectorXd DataInterpolation::CalculateCoeff() {
    VectorXd a;
    if(nbPoint>11 || degree <4){
        a = PieceWise();
    }
    else {
        a = Polynomial();
    }
    return a;
}

VectorXd DataInterpolation::Polynomial() {
    degree = nbPoint -1;
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
    return a;
}

VectorXd DataInterpolation::PieceWiseContinuous(){
    int unknownNb = (nbPoint-1)*(degree+1);
    MatrixXd A(unknownNb,unknownNb);
    VectorXd b(unknownNb);
    for(int i = 0;i<unknownNb;i++){
        for(int j = 0;j<unknownNb;j++){
            A(i,j)=0;
        }
        b(i)=0;
    }
    int j = 0;
    int f = 0;
    VectorXd a(unknownNb);
    switch(degree){
        case 1: {
            for (int i = 0; i<unknownNb;i=i+2){
                a(i)= (y[j+1]-y[j])/(x[j+1]-x[j]);
                a(i+1)= y[j]-x[j]*(y[j+1]-y[j])/(x[j+1]-x[j]);
                j+=1;
            }
            break;
        }
        case 2:{
            for(int i = 0;i<(degree-1)*2;i = i+2){
                A(i,j) = pow(x[f],2);
                A(i,j+1) = pow(x[f],1);
                A(i,j+2) = pow(x[f],0);
                A(i+1,j) = pow(x[f+1],2);
                A(i+1,j+1) = pow(x[f+1],1);
                A(i+1,j+2) = pow(x[f+1],0);
                b(i)=y[f];
                b(i+1)=y[f+1];
                j = j+3;
                f = f+1;
            }
            A((nbPoint-1)*2,0)=1;
            j = 0;
            f = 1;
            for(int i = (nbPoint-1)*2+1;i<(unknownNb);i++){
                A(i,j)=2*x[f];
                A(i,j+1)=1;
                A(i,j+3)=-2*x[f];
                A(i,j+4)=-1;
                j = j+3;
                f = f+1;
            }
            a = A.colPivHouseholderQr().solve(b);
            break;
        }
        case 3:{
            for(int i = 0;i<(nbPoint-1)*2;i = i+2){
                A(i,j) = pow(x[f],3);
                A(i,j+1) = pow(x[f],2);
                A(i,j+2) = pow(x[f],1);
                A(i,j+3) = pow(x[f],0);
                A(i+1,j) = pow(x[f+1],3);
                A(i+1,j+1) = pow(x[f+1],2);
                A(i+1,j+2) = pow(x[f+1],1);
                A(i+1,j+3) = pow(x[f+1],0);
                b(i)=y[f];
                b(i+1)=y[f+1];
                j = j+4;
                f = f+1;
            }
            j = 0;
            f = 1;
            for(int i = (nbPoint-1)*2;i<3*nbPoint-4;i++){
                A(i,j)=3*pow(x[f],2);
                A(i,j+1)=2*x[f];
                A(i,j+2)=1;
                A(i,j+4)=-3*pow(x[f],2);
                A(i,j+5)=-2*x[f];
                A(i,j+6)=-1;
                j = j+4;
                f = f+1;
            }
            j = 0;
            f = 1;
            for(int i = 3*nbPoint-4;i<4*nbPoint-6;i++){
                A(i,j)=6*x[f];
                A(i,j+1)=2;
                A(i,j+4)=-6*x[f];
                A(i,j+5)=-2;
                j = j+4;
                f = f+1;
            }
            j = 0;
            f = 0;
            for(int i = 4*nbPoint-6;i<unknownNb;i++){
                A(i,j)=6*x[f];
                A(i,j+1)=2;
                j = j+4*(nbPoint-2);
                f = f+nbPoint-1;
            }
            a = A.colPivHouseholderQr().solve(b);
            break;
        }
    }
    return a;
}

VectorXd DataInterpolation::PieceWise(){
    int funcNb,resDegree,unknownNb;
    funcNb = floor((nbPoint-1)/nbPoint);
    resDegree = (nbPoint-1) - (funcNb*nbPoint);
    if(resDegree>0) {
        unknownNb = funcNb * (nbPoint + 1) + resDegree + 1;
    }else{
        unknownNb = funcNb * (nbPoint + 1);
    }
    VectorXd a(unknownNb);
    for(int i = 0;i<unknownNb;i++){
        a(i)=0;
    }
    int f = 0;
    for(int i = 0;i<funcNb;i++){
        double *xi = new double[degree+1];
        double *yi = new double[degree+1];
        for(int j = 0;j<degree+1;j++) {
            xi[j] = x[i*(degree)+j];
            yi[j] = y[i*(degree)+j];
            cout << xi[j]<< " & "<<yi[j]<<endl;
        }
        Points P(xi,yi,degree+1,degree);
        DataFitting df(P);
        VectorXd coeff =  df.CalculateCoeff();
        for(int j = 0;j<degree+1;j++) {
            a(f+j) = coeff(j);
        }
        f = f+degree+1;
        cout << " new "<<endl;
        delete[] xi;
        delete[] yi;
    }
    if(resDegree>0){
        double *xi2 = new double[resDegree+1];
        double *yi2 = new double[resDegree+1];
        for(int j = 0;j<resDegree+1;j++) {
            xi2[j] = x[funcNb*(degree)+j];
            yi2[j] = y[funcNb*(degree)+j];
            cout << xi2[j]<< " & "<< yi2[j]<<endl;
        }
        Points P2(xi2,yi2,degree+1,degree);
        DataFitting df2(P2);
        VectorXd coeff2 =  df2.CalculateCoeff();
        for(int j = 0;j<resDegree+1;j++) {
            a(f+j) = coeff2(j);
        }
    }
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
