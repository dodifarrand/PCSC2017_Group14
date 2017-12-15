#ifndef APPR0XIMATION
#define APPR0XIMATION
#include <Eigen/Dense>
#include "Points.hpp"
#include <iostream>

using namespace Eigen;

class Approximation {

public:
    // Default constructor
    Approximation();
    // Alternate constructors
    Approximation(Points P);
    // Destructor
    ~Approximation(){};//std::cout << "Destroy object Approximation" << std::endl;}

    virtual VectorXd CalculateCoeff();  // base method to compute the coefficients
    virtual void printSolution(VectorXd a); // base method to print the solution
    virtual double CalculateError(VectorXd a);  // base method to comute the error

protected:
    // Private data
    double *x;  // x coordinates of points to approximate
    double *y;  // y coodrinates of points to approximate
    int nbPoint;
    int degree;
    std::string type;
};

class Fitting: public Approximation {
public:
    Fitting(Points P):Approximation(P){};
    VectorXd CalculateCoeff();
    double CalculateError(VectorXd a);
    void printSolution(VectorXd a);
    ~Fitting(){};

};

class Interpolation: public Approximation {

public:
    Interpolation(Points P):Approximation(P){};
    virtual VectorXd CalculateCoeff();
    void printSolution(VectorXd a);
    double CalculateError(VectorXd a);
    ~Interpolation(){};
};

class PieceWiseInterpolation: public Approximation{
public:
    PieceWiseInterpolation(Points P):Approximation(P){};
    virtual VectorXd CalculateCoeff();
    VectorXd PieceWise();
    VectorXd PieceWiseContinuous();
    void printSolution(VectorXd a);
    double CalculateError(VectorXd a);
    ~PieceWiseInterpolation(){};
};
#endif


