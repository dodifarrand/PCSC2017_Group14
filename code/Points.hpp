#ifndef POINTS
#define POINTS

#include <Eigen/Dense>
using namespace Eigen;

#include <string>

class Points {
public:
    // Default constructor
    Points();
    // Alternate constructors
    Points(double *x, double *y, int nbPoint, int degree, std::string type);
    // Destructor
    virtual ~Points() {}

    // Private data
    double *m_x;
    double *m_y;
    int m_nbPoint;
    int m_degree;
    std::string m_type;
};

#endif


