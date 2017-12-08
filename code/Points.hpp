#ifndef POINTS
#define POINTS

#include <Eigen/Dense>
using namespace Eigen;


class Points {
public:
    // Default constructor
    Points();
    // Alternate constructors
    Points(double *x, double *y, int nbPoint, int degree){
        this->x = x;
        this->y = y;
        this->nbPoint = nbPoint;
        this->degree = degree;
    }
    // Destructor
    virtual ~Points() {}

    // Private data
    double *x;
    double *y;
    int nbPoint;
    int degree;
};

#endif


