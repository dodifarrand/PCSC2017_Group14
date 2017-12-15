//
// Created by Anouk Allenspach on 11.12.17.
//

#ifndef PCSC_PROJECT6_TESTING_H
#define PCSC_PROJECT6_TESTING_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cassert>
#include <cmath>

/**
* This class creates points from a function given by the user
*/
class FuctionApprox{
private:

    double m_a;    // /*!< beginning of interval */
    double m_b;    // /*!< end of interval */
    int N_points;   // /*!< number of points to generate */
    double (*my_p_function)(double x);  // /*!< function pointer to be used for any function */

public:

    void SetInterval(double a, double b);
    FuctionApprox();
    FuctionApprox(std::string file_name);
    FuctionApprox(std::string file_name, double (*pf)(double));
    void WritePoints(std::string func_name);
    void SetFunctionPointer(std::string func_name);

};
#endif //PCSC_PROJECT6_TESTING_H
