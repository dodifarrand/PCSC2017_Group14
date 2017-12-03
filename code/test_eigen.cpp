#include <iostream>
#include <Eigen/Dense>
using namespace std;
using namespace Eigen;

int main()
{
    MatrixXf A(3,3);
    Vector3f b;
    A << 5,21,111,21,111,651,111,651,4035;
    b << 25, 127, 739;
    cout << "Here is the matrix A:\n" << A << endl;
    cout << "Here is the vector b:\n" << b << endl;
    Vector3f x = A.colPivHouseholderQr().solve(b);
    cout << "The solution is:\n" << x << endl;
}


// y= + (1.8701)x^0 + (0.3333)x^1 + (0.0779)x^2