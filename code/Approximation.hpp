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
    virtual ~Approximation() {std::cout << "Destroy object Approximation" << std::endl;}

    virtual VectorXd CalculateCoeff();
    virtual void printSolution(VectorXd a);
    virtual double CalculateError(VectorXd a);

protected:
    // Private data
    double *x;
    double *y;
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

};

class Interpolation: public Approximation {

public:
    Interpolation(Points P):Approximation(P){};
    virtual VectorXd CalculateCoeff();
    void printSolution(VectorXd a);
    double CalculateError(VectorXd a);
};

class PieceWiseInterpolation: public Approximation{
public:
    PieceWiseInterpolation(Points P):Approximation(P){};
    virtual VectorXd CalculateCoeff();
    VectorXd PieceWise();
    VectorXd PieceWiseContinuous();
    void printSolution(VectorXd a);
    double CalculateError(VectorXd a);
};
#endif


