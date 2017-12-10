//
// Created by Anouk Allenspach on 10.12.17.
//

#ifndef PCSC_PROJECT6_READPOINTS_H
#define PCSC_PROJECT6_READPOINTS_H

#include "ReadFile.h"
#include "ReadInput.h"

class ReadPointCoord : public ReadFile
{
private:
    double* m_x;
    double* m_y;
    int mnPoints;
public:
    ReadPointCoord();
    ~ReadPointCoord();
    void ReadData();

};
#endif //PCSC_PROJECT6_READPOINTS_H
