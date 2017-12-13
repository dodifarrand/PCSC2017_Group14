#ifndef POINTS
#define POINTS

#include <Eigen/Dense>
using namespace Eigen;

#include <string>
/**
* This is our points class
*/
class Points {
public:
    // Default constructor
    Points();
    // Alternate constructors
    Points(double *x, double *y, int nbPoint, int degree);
    // Destructor
    virtual ~Points() {}

    // Private data
    double *m_x;    // /*!< x vector */
    double *m_y;    // /*!< y vector */
    int m_nbPoint; // /*!< number of points */
    int m_degree;// /*!< degree */
    //std::string m_type;// /*!< type */
};

#endif


