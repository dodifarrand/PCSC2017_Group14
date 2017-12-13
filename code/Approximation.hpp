#ifndef APPR0XIMATION
#define APPR0XIMATION
#include <Eigen/Dense>
#include "Points.hpp"

using namespace Eigen;


class Approximation {
public:
    // Default constructor
    Approximation();
    // Alternate constructors
    Approximation(Points P){
        this->x = P.x;
        this->y = P.y;
        this->nbPoint = P.nbPoint;
        this->degree = P.degree;
    }
    // Destructor
    virtual ~Approximation() {}

    virtual VectorXd CalculateCoeff() = 0;

protected:
    // Private data
    double *x;
    double *y;
    int nbPoint;
    int degree;
};

class DataFitting: public Approximation {
public:
    DataFitting(Points P):Approximation(P){};
    virtual VectorXd CalculateCoeff(){
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
    double CalculateError(VectorXd a);

};

class DataInterpolation: public Approximation {
public:
    DataInterpolation(Points P):Approximation(P){};
    virtual VectorXd CalculateCoeff() {
            VectorXd a;
            if(nbPoint>11 || degree <8){
                a = PieceWise();
            }
            else {
                a = Polynomial();
            }
            return a;
        }
    VectorXd Polynomial(){degree = nbPoint -1;
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
        return a;}
    VectorXd PieceWise(){
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
              //  std::cout << xi[j]<< " & "<<yi[j]<<std::endl;
            }
            Points P(xi,yi,degree+1,degree);
            DataFitting df(P);
            VectorXd coeff =  df.CalculateCoeff();
            for(int j = 0;j<degree+1;j++) {
                a(f+j) = coeff(j);
            }
            f = f+degree+1;
          //  std::cout << " new "<<std::endl;
            delete[] xi;
            delete[] yi;
        }
        if(resDegree>0){
            double *xi2 = new double[resDegree+1];
            double *yi2 = new double[resDegree+1];
            for(int j = 0;j<resDegree+1;j++) {
                xi2[j] = x[funcNb*(degree)+j];
                yi2[j] = y[funcNb*(degree)+j];
         //       cout << xi2[j]<< " & "<< yi2[j]<<endl;
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
    VectorXd PieceWiseContinuous();
};

#endif


