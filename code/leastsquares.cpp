#include <iostream>
#include <Eigen/Dense>
#include <vector>
#include <math.h>
using namespace std;
using namespace Eigen;
using std::vector;

VectorXd CalculateCoeff(double *x, double *y, int pointNb, int polDegree);
VectorXd pieceWise(double *x, double *y, int pointNb,int polDegree);
VectorXd pieceWise2(double *x, double *y, int pointNb,int polDegree);
vector<double> linspace(double a, double b, int n);
double CalculateError(VectorXd a, double *x, double *y,int nbPoint);

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
    //for(int i = 0;i<10;i++){
    //    xi[i]=-10+2.5*i;
    //    yi[i]= 0.003*pow(xi[i],6) - 6*pow(xi[i],4) - 3;
    //    cout << xi[i] << " & " << yi[i]<< endl;
    //}

    //VectorXd coeff2 = pieceWise2(xi, yi,9,4);

    VectorXd coeff1 = CalculateCoeff(xi,yi,9,8);
    //VectorXd coeff2 = pieceWise(xi, yi,5,2);
    //double err = CalculateError(coeff1,xi,yi,9);
    cout << "The 1st solution is:\n" << coeff1 << endl;
    //cout << "The 2nd solution is:\n" << coeff2 << endl;
    //cout << "Error : " << err  << endl;
    delete[] xi;
    delete[] yi;
    delete[] funci;

}

VectorXd CalculateCoeff(double *x, double *y, int pointNb, int polDegree){
    double *val = new double[2*polDegree+1];
    double *val2 = new double[polDegree+1];
    MatrixXd A(polDegree+1,polDegree+1);
    VectorXd b(polDegree+1);
    for(int n = 0; n<2*polDegree+1;n++){
        val[n]=0;
        val2[n]=0;
        for(int i = 0; i<pointNb;i++){
            val[n]+=pow(x[i],2*polDegree-n);
            if(n<polDegree+1){
                val2[n] += pow(x[i],polDegree-n)*y[i];
            }
        }
    }
    for(int i = 0; i<polDegree+1;i++){
        for(int j = 0; j<polDegree+1;j++){
            A(i,j)=val[i+j];
        }
        b(i)=val2[i];
    }
    VectorXd a = A.colPivHouseholderQr().solve(b);
    delete[] val;
    delete[] val2;
    return a;
}

VectorXd pieceWise(double *x, double *y, int pointNb,int polDegree){
    int unknownNb = (pointNb-1)*(polDegree+1);
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
    switch(polDegree){
        case 1: {
            for (int i = 0; i<unknownNb;i=i+2){
                a(i)= (y[j+1]-y[j])/(x[j+1]-x[j]);
                a(i+1)= y[j]-x[j]*(y[j+1]-y[j])/(x[j+1]-x[j]);
                j+=1;
            }
            break;
        }
        case 2:{
            for(int i = 0;i<(pointNb-1)*2;i = i+2){
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
            A((pointNb-1)*2,0)=1;
            j = 0;
            f = 1;
            for(int i = (pointNb-1)*2+1;i<(unknownNb);i++){
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
            for(int i = 0;i<(pointNb-1)*2;i = i+2){
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
            for(int i = (pointNb-1)*2;i<3*pointNb-4;i++){
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
            for(int i = 3*pointNb-4;i<4*pointNb-6;i++){
                A(i,j)=6*x[f];
                A(i,j+1)=2;
                A(i,j+4)=-6*x[f];
                A(i,j+5)=-2;
                j = j+4;
                f = f+1;
            }
            j = 0;
            f = 0;
            for(int i = 4*pointNb-6;i<unknownNb;i++){
                A(i,j)=6*x[f];
                A(i,j+1)=2;
                j = j+4*(pointNb-2);
                f = f+pointNb-1;
            }
            a = A.colPivHouseholderQr().solve(b);
            break;
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

VectorXd pieceWise2(double *x, double *y, int pointNb,int polDegree){
    int funcNb,resDegree,unknownNb;
    funcNb = floor((pointNb-1)/polDegree);
    resDegree = (pointNb-1) - (funcNb*polDegree);
    if(resDegree>0) {
        unknownNb = funcNb * (polDegree + 1) + resDegree + 1;
    }else{
        unknownNb = funcNb * (polDegree + 1);
    }
    VectorXd a(unknownNb);
    for(int i = 0;i<unknownNb;i++){
        a(i)=0;
    }
    int f = 0;
    for(int i = 0;i<funcNb;i++){
        double *x_p = new double[polDegree+1];
        double *y_p = new double[polDegree+1];
        for(int j = 0;j<polDegree+1;j++) {
            x_p[j] = x[i*(polDegree)+j];
            y_p[j] = y[i*(polDegree)+j];
            cout << x_p[j]<< " & "<<y_p[j]<<endl;
        }
        VectorXd coeff =  CalculateCoeff(x_p,y_p,polDegree+1,polDegree);
        for(int j = 0;j<polDegree+1;j++) {
            a(f+j) = coeff(j);
        }
        f = f+polDegree+1;
        cout << " new "<<endl;
        delete[] x_p;
        delete[] y_p;
    }
    if(resDegree>0){
        double *xi2 = new double[resDegree+1];
        double *yi2 = new double[resDegree+1];
        for(int j = 0;j<resDegree+1;j++) {
            xi2[j] = x[funcNb*(polDegree)+j];
            yi2[j] = y[funcNb*(polDegree)+j];
            cout << xi2[j]<< " & "<< yi2[j]<<endl;
        }
        VectorXd coeff2 =  CalculateCoeff(xi2,yi2,resDegree+1,resDegree);
        for(int j = 0;j<resDegree+1;j++) {
            a(f+j) = coeff2(j);
        }
    }
    return a;
}


double CalculateError(VectorXd a, double *x, double *y,int nbPoint){
    int degree = a.size()-1;
    double err = 0;
    double *fx = new double[nbPoint];
    for(int i = 0; i<nbPoint;i++){
        fx[i] = 0;
        for(int j = 0; j<degree+1;j++){
            fx[i] += pow(x[i],degree-j)*a(j);
        }
        err += pow(y[i]-fx[i],2);
    }
    return err;
}