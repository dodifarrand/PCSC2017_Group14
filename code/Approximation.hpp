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
        this->x = P.m_x;
        this->y = P.m_y;
        this->nbPoint = P.m_nbPoint;
        this->degree = P.m_degree;
        this->type = P.m_type;
    }
    // Destructor
    virtual ~Approximation() {}

    virtual VectorXd CalculateCoeff() = 0;

protected:
    // Private data
    double *x;
    double *y;
    int nbPoint;
    int degree;
    std::string type;
};
#endif


