#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

void CalculateCoeff(int *x, int *y, int pointNb, int polDegree);

int main()
{
    int *xi = new int[6];
    int *yi = new int[6];
    xi[0] = 1;
    xi[1] = 2;
    xi[2] = 3;
    xi[3] = 4;
    xi[4] = 5;
    xi[5] = 6;
    yi[0] = 2;
    yi[1] = 5;
    yi[2] = 12;
    yi[3] = 18;
    yi[4] = 40;
    yi[5] = 46;
    //int yi[3] = {1,4,9};
    //VectorXd y;
    //MatrixXd A;
    CalculateCoeff(xi,yi,6,5);
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