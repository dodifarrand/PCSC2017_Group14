//
// Created by Anouk Allenspach on 13.12.17.
//

#ifndef PCSC_PROJECT6_DATAFITTING_H
#define PCSC_PROJECT6_DATAFITTING_H

#include "Approximation.hpp"

class DataFitting: public Approximation {
public:
    DataFitting(Points P):Approximation(P){};
    virtual VectorXd CalculateCoeff();
    double CalculateError(VectorXd a);

};


#endif //PCSC_PROJECT6_DATAFITTING_H
