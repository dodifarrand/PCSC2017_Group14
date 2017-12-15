#ifndef POINTS
#define POINTS

#include <Eigen/Dense>
using namespace Eigen;

#include <string>
#include "Config.h"

/**
* This is our points class
*/
class Points{
public:
    // Default constructor
    Points();
    // Alternate constructors
    Points(double *x, double *y, int nbPoint, int degree, std::string type = "");   // for knows x and y, known degree and optionally type
    // Destructor
    ~Points();
    int CountLines(std::string data_file);   // counts the number of lines
    double* x();    // return x_coordinates
    double* y();    // returns y_coordinates
    int GetNPoints();   // returns number of points
    Points(std::string a_file_name);
    void ReadData();
    std::string* ReadConfig();
    std::string GetType();  // returns the type


    // Private data
    friend class Approximation;


private:
    double *m_x;    // /*!< x vector */
    double *m_y;   // /*!< y vector */
    int m_nbPoint; // /*!< number of points */
    int m_degree;// /*!< degree */
    char const* data_file;// /*!< file name of point file */
    std::string m_type;// /*!< type */
    char const* mfile_name;
    //std::string file_name_points;
};
//
// Created by Anouk Allenspach on 10.12.17.
//

#endif

