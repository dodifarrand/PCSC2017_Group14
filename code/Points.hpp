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
    Points(double *x, double *y, int nbPoint, int degree, std::string type = "");   // for knows x and y, known degree and optionally type
    // Destructor
    //~Points();
    int CountLines();   // counts the number of lines
    double* x();    // return x_coordinates
    double* y();    // returns y_coordinates
    int GetNPoints();   // returns number of points
    Points(std::string a_file_name, int degree, std::string type = "");
    void ReadData();
    std::string GetType();  // returns the type


    // Private data
    friend class Approximation;


private:
    double *m_x;    // /*!< x vector */
    double *m_y;    // /*!< y vector */
    int m_nbPoint; // /*!< number of points */
    int const m_degree;// /*!< degree */
    char const* file_name;// /*!< file name of point file */
    std::string m_type;// /*!< type */
};
//
// Created by Anouk Allenspach on 10.12.17.
//

#endif

