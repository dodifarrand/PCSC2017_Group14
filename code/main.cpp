#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <vector>


// on monday, ask if we can use this or if we should implement gaussian elimination
template<class T> void BackSubst(T**& B, double*& a, const int n2);
template<class T> void Gauss(T**&A, T*& b, double*& a, const int n);
template<class T> void Alloc(T**& M, const int rows, const int cols);
template<class T> void Alloc(T*& v, const int length);
template<class T> void Delete(T**& M, const int rows, const int cols);
template<class T> void Delete(T*& v);
template<class T> void Print(T**& M, const int rows, const int cols);
template<class T> void Print(T*& v, const int length);



int main(int argc, char* argv[]){


// ******************************************************************************************************
    // Read file
    std::cout << "Enter filename and press enter\n";
    std::string f_name;
    std::getline(std::cin, f_name);

    f_name = f_name + ".csv";
    const char* file_name = f_name.c_str();
    std::ifstream read_file(file_name);

    if(!read_file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return 1;
    }

    int i = 0;
    // start of reading file, get number of lines
    while (!read_file.eof())
    {
        std::string line;
        getline(read_file, line);
        //std::cout << line[0];
       // std::cout << line << std::endl;
        if (line.compare("") != 0){
            i++;
        }

    }


    // for the found number of rows
    std::cout << "Number of rows = " << i << "\n";
    read_file.close();
    int rows = i;

    // read the file into the vectors
    FILE * pFile = fopen(file_name,"r");    // use file pointer

    // adapt for case of double, maybe make a template
    int x[rows];
    int y[rows];
    int N = rows;

    // reset the read_file state
    read_file.clear();
    read_file.seekg(std::ios::beg);

    for (int i = 0; i < rows; i++) {

            fscanf(pFile, "%i,%i", &x[i], &y[i]);

            std::cout << "x[" << i << "]" << ": " << x[i] << ", y[" << i << "]: " <<  y[i] << std::endl;

    }
    read_file.close();
// ******************************************************************************************************
    // end of read file
    int n; // degree of polynomial
    if (argc < 3) {
        std::cout << "Enter degree of polynomial do you want to use?" << std::endl;
        // add assert statement of check for validity
        std::cin >> n;
    }
    else if (argc == 3){
        n = atoi(argv[2]);
    }
    // now we have degree of polynomial n



// *****************************************************************************************************
    // note: this we should also have for int and double
    // start creating arrays to input into least square method
    // vector of sigmas to be used in augmented matrix
    double X[2*n+1];    // will store the sigmas
    for (int i = 0; i < 2*n+1; i++){
        X[i] = 0.0;
        for (int j = 0; j < N; j++){
            X[i]=X[i]+std::pow(x[j],i); // X[i] = sum(for j = 0 to N: x[j]^i)
        }
    }

    // augmented matrix B
    double A[n+1][n+1];
    double a[n+1];  // vector of coefficients ex: a[2] contains coefficient that multiplies x^2

    for (int i = 0; i < n+1; i++){
        for (int j = 0; j< n+1; j++){
            A[i][j]=X[i+j];
        }
    }
    // will store the rhs values
    double b[n+1];
    for (int i = 0; i < n+1; i++){
        b[i]=0;
        for (int j = 0; j < N; j++){
            b[i]=b[i]+std::pow(x[j],i)*y[j];
        }

    }
// ******************************************************************************************************


    std::cout<<"\nThe Normal Matrix is as follows:\n";
    for (int i = 0; i < n+1; i++) //print the Normal-augmented matrix
    {
        for (int j = 0; j < n+1; j++){
            std::cout<<A[i][j]<<std::setw(6);

        }
        std::cout<<"\n";
    }


    return 0;

}

template<class T> void BackSubst(T**& B, double*& a, const int n2){
    for (int i = n2-1; i >= 0; i--)    {        //back-substitution
        //x is an array whose values correspond to the values of
        //x,y,z..
        a[i] = B[i][n2];   //make the variable to be calculated equal to the
        // rhs of the last equation

        for (int j = 0; j < n2; j++) {
            if (j != i) {       //then subtract all the lhs values except the
                //   coefficient of the variable whose value is being
                // calculated
                a[i] = a[i] - B[i][j] * a[j];
            }
            a[i] = a[i] / B[i][i];      //now finally divide the rhs by the coefficient
            // of the variable to be calculated
        }
    }

}

template<class T> void Gauss(T**&A, T*& b, double*& a, const int n) {

    double** B;
    B = new double*[n+1];
    for (int i = 0; i<n+2; i++){
        B[i] = new double[n+1];
    }


    for (int i = 0; i < n + 1; i++) {
        for (int j = 0; j < n + 1; j++) {
            B[i][j] = A[i][j];
        }
        B[i][n + 1] = b[i]; //load the values of b as the last column of A
        // A(Normal Matrix but augmented)
    }

    int n2 = n + 1;
    for (int i = 0; i < n2; i++) //From now Gaussian Elimination starts(can be
//  ignored) to solve the set of linear equations (Pivotisation)
        for (int k = i + 1; k < n2; k++) {
            if (B[i][i] < B[k][i]) {
                for (int j = 0; j < n2 + 1; j++) {
                    double temp = B[i][j];
                    B[i][j] = B[k][j];
                    B[k][j] = temp;
                }
            }
        }


    for (int i = 0; i < n - 1; i++) { //loop to perform the gauss elimination
        for (int k = i + 1; k < n; k++) {
            double t = B[k][i] / B[i][i];
            for (int j = 0; j < n + 1; j++) {
                B[k][j] = B[k][j] - t * B[i][j]; //make the elements below the pivot
                //elements equal to zero or elimnate the variables
            }
        }
    }
    BackSubst(B,a,n2);
}
template<class T> void Alloc(T**& M, const int rows, const int cols){
        M = new T *[rows];
        for (int i = 0; i < rows; i++) {
            M[i] = new T[cols];
        }
}


template<class T> void Delete(T **&M, const int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] M[i];
    }
    delete[] M;
}

template<class T> void Print(T**& A, const int rows, const int cols){
    for (int i = 0; i<rows; i++) {
        for (int j = 0; j < cols; j++) {
            std::cout << A[i][j] << " " ;
        }
        std::cout << std::endl;
    }

}
template<class T> void Alloc(T*& v, const int length){
    v = new T *[length];
}

template<class T> void Delete(T *&v) {

    delete[] v;
}

template<class T> void Print(T*& v, const int length){
    for (int i = 0; i<length; i++) {
        std::cout << v[i]  << std::endl;;
    }

}