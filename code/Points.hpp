#ifndef POINTS
#define POINTS

#include <Eigen/Dense>
using namespace Eigen;

#include <string>
#include "Config.h"
/**
* This is our points class
*/
class Points: public Config {
public:
    // Default constructor
    Points();
    // Alternate constructors
    Points(double *x, double *y, int nbPoint, int degree);
    Points(std::string point_file);
    // Destructor
    virtual ~Points() {}
    int CountLines(std::string file_name);
    double* x();
    double* y();
    int GetNPoints();


    // Private data
    friend class Approximation;


private:
    double *m_x;    // /*!< x vector */
    double *m_y;    // /*!< y vector */
    int m_nbPoint; // /*!< number of points */
    int m_degree;// /*!< degree */
    //std::string m_type;// /*!< type */
};

#endif


