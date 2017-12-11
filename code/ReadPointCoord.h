//
// Created by Anouk Allenspach on 10.12.17.
//

#ifndef PCSC_PROJECT6_READPOINTS_H
#define PCSC_PROJECT6_READPOINTS_H

#include "Config.h"


class ReadPointCoord : public Config
{
private:
    double* m_x;
    double* m_y;
    int mnPoints;
    char const* file_name;
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
