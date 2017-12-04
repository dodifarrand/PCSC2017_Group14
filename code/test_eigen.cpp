#include <iostream>
#include <Eigen/Dense>
#include <cmath>
using namespace std;
using namespace Eigen;



int main()
{

    Matrix4f A;
    Vector3f b;
    //int x2[3];
    //double a=0;
    //for(int i=0;i<3;i++){
    //    for(int j=0;j<3;j++){
    //        A(i,j)= i+1;
    //    }
    //}
    A << 6,21,91,441,21,91,441,2275,91,441,2275,12201,67171;
    b << 91,441,2275,12201;
    cout << "Here is the matrix A:\n" << A << endl;
    cout << "Here is the vector b:\n" << b << endl;
    Vector4f x = A.colPivHouseholderQr().solve(b);
    cout << "The solution is:\n" << x << endl;
    //for(int i=0;i<3;i++){
    //    x2[i] = x[i];
    //    cout << x2[i]<< endl;
    //    a += b[i];
    //}
    //cout << a;
}
