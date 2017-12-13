//
// Created by Anouk Allenspach on 13.12.17.
//

#ifndef PCSC_PROJECT6_DATAINTERPOLATION_H
#define PCSC_PROJECT6_DATAINTERPOLATION_H

#include "Approximation.hpp"

class DataInterpolation: public Approximation {

public:
    DataInterpolation(Points P):Approximation(P){};
    virtual VectorXd CalculateCoeff();
    VectorXd PieceWise();
    VectorXd Polynomial();
    VectorXd PieceWiseContinuous();
};


#endif //PCSC_PROJECT6_DATAINTERPOLATION_H
