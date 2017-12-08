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

//class DataFitting: public Approximation {
//public:
//    DataFitting(double *x, double *y, int nbPoint, int degree):Approximation(x, y, nbPoint,  degree);
//    virtual VectorXd CalculateCoeff(double *x, double *y, int pointNb, int polDegree);
//
//};
//
//class DataInterpolation: public Approximation {
//public:
//    DataInterpolation(double *x, double *y, int nbPoint, int degree):Approximation(x, y, nbPoint,  degree);
//    virtual VectorXd CalculateCoeff(double *x, double *y, int pointNb, int polDegree);
//};

#endif


