#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

void CalculateCoeff(int *x, int *y, int pointNb, int polDegree);
void pieceWiseLinear(int *x, int *y, int pointNb,int polDegree);

int main()
{
    int *xi = new int[6];
    int *yi = new int[6];
    xi[0] = 1;
    xi[1] = 2;
    xi[2] = 3;
    xi[3] = 4;
    xi[4] = 5;
    //xi[5] = 6;
    yi[0] = 1;
    yi[1] = 10;
    yi[2] = 5;
    yi[3] = 18;
    yi[4] = 40;
    //yi[5] = 46;
    //int yi[3] = {1,4,9};
    //VectorXd y;
    //MatrixXd A;
    //CalculateCoeff(xi,yi,2,2);
    pieceWiseLinear(xi, yi, 5,2);
}

void CalculateCoeff(int *x, int *y, int pointNb, int polDegree){
    int *val = new int[2*polDegree+1];
    MatrixXd A(polDegree+1,polDegree+1);
    VectorXd b(polDegree+1);
    int *val2 = new int[polDegree+1];
    for(int n = 0; n<=2*polDegree;n++){
        val[n]=0;
        val2[n]=0;
        for(int i = 0; i<pointNb;i++){
            val[n]+=pow(x[i],n);
            if(n<polDegree+1){
                val2[n] += pow(x[i],n)*y[i];
            }
        }
    }
    for(int i = 0; i<polDegree+1;i++){
        for(int j = 0; j<polDegree+1;j++){
            A(i,j)=val[i+j];
        }
        b(i)=val2[i];
    }
    cout << "Here is the matrix A:\n" << A << endl;
    cout << "Here is the vector b:\n" << b << endl;
    VectorXd a = A.colPivHouseholderQr().solve(b);
    cout << "The solution is:\n" << a << endl;
}

void pieceWiseLinear(int *x, int *y, int pointNb,int polDegree){
    int unknownNb = (pointNb-1)*(polDegree+1);
    MatrixXd A(unknownNb,unknownNb);
    VectorXd b(unknownNb);
    //b<<y[0],y[1],y[1],y[2],0;
    for(int i = 0;i<unknownNb;i++){
        for(int j = 0;j<unknownNb;j++){
            A(i,j)=0;
        }
        b(i)=0;
    }
    int j = 0;
    int f = 0;
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
    //A((pointNb-1)*2,3)=-1;
    //A((pointNb-1)*2+1,3)=1;
    //A((pointNb-1)*2+1,6)=-1;
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
    //A(0,0)=x[0];
    //A(0,1)=1;
    //A(1,0)=x[1];
    //A(1,1)=1;
    //A(2,2)=pow(x[1],2);
    //A(2,3)=x[1];
    //A(2,4)=1;
    //A(3,2)=pow(x[2],2);
    //A(3,3)=x[2];
    //A(3,4)=1;
    //A(4,0)=1;
    //A(4,2)=-2*x[1];
    //A(4,3)=-1;
    cout << "Here is the matrix A:\n" << A << endl;
    cout << "Here is the vector b:\n" << b << endl;
    VectorXd a = A.colPivHouseholderQr().solve(b);
    cout << "The solution is:\n" << a << endl;

}