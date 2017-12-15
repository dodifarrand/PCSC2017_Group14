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
    int nbPoint;    // number of points given to be used for approximation
    int degree; // degree of approximation to use
    std::string type;   // type of method to do for the approximation
};

class Fitting: public Approximation {
public:
    Fitting(Points P):Approximation(P){};   // construnctor creating object from points object
    VectorXd CalculateCoeff();  // calculate the coefficients in case of data fitting
    double CalculateError(VectorXd a);  // overriden method to calculate the error if data fitting was done
    void printSolution(VectorXd a); // overriden method to print solution in the fitting class
    ~Fitting(){};   // destructor for the fitting class

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


