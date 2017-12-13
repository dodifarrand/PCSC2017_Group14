//
// Created by Anouk Allenspach on 10.12.17.
//

#ifndef PCSC_PROJECT6_READPOINTS_H
#define PCSC_PROJECT6_READPOINTS_H

#include "Config.h"

/**
* This is our ReadPointCoord class
*/
class ReadPointCoord : public Config
{
private:
    double* m_x;// /*!< vector of x coords */
    double* m_y;// /*!< vector of y coords */
    int mnPoints;// /*!< number of points */
    char const* file_name;// /*!< file name of point file */
public:
    ReadPointCoord();
    void ReadData();
    void CountLines();
    ReadPointCoord(char const* f_name);
    double* x();
    double* y();
    ~ReadPointCoord();
    int GetNPoints();
};
#endif //PCSC_PROJECT6_READPOINTS_H
