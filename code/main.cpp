#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>


int main(int argc, char* argv[]){


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
        std::cout << line[0];
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
    FILE * pFile = fopen(file_name,"r");

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

    int n;
    std::cout << "Enter degree of polynomial do you want to use?" << std::endl;$
    // add assert statement of check for validity
    std::cin >> n;


    // start creating arrays to input into least square method
    // vector of sigmas to be used in augmented matrix
    double X[2*n+1];    // will store the sigmas
    for (int i = 0; i < 2*n+1; i++){
        X[i] = 0.0;
        for (int j = 0; j < N; j++){
            X[i]=X[i]+std::pow(x[j],i); // X[i] = sum(for j = 0 to N: x[j]^i)
        }
    }

    // augmented matrix
    double B[n+1][n+2];
    double a[n+1];  // vector of coefficients ex: a[2] contains coefficient that multiplies x^2

    for (int i = 0; i < n+1; i++){
        for (int j = 0; j< n+2; j++){
            B[i][j]=X[i+j];
        }
    }
    double Y[n+1];
    for (int i = 0; i < n+1; i++){
        Y[i]=0;
        for (int j = 0; j < N; j++){
            Y[i]=Y[i]+pow(x[j],i)*y[j];
        }

    }
    for (int i = 0; i < n+1; i++){
        B[i][n+1]=Y[i];     // load y values into last column of B
    }

    std::cout<<"\nThe Normal(Augmented Matrix) is as follows:\n";
    for (int i = 0; i < n+1; i++) //print the Normal-augmented matrix
    {
        for (int j = 0; j < n+2; j++){
            std::cout<<B[i][j]<<std::setw(16);

        }
        std::cout<<"\n";
    }


    return 0;

}