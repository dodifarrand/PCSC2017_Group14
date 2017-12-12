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

    virtual VectorXd CalculateCoeff();

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
    virtual VectorXd CalculateCoeff();
    double CalculateError(VectorXd a);

};

class DataInterpolation: public Approximation {
public:
    DataInterpolation(Points P):Approximation(P){};
    virtual VectorXd CalculateCoeff();
    VectorXd Polynomial();
    VectorXd PieceWise();
    VectorXd PieceWiseContinuous();
};

#endif


