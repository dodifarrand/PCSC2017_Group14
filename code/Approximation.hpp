#ifndef APPR0XIMATION
#define APPR0XIMATION

#include <Eigen/Dense>
using namespace Eigen;


class Approximation {
public:
    // Default constructor
    Approximation();
    // Alternate constructors
    Approximation(const double *x,const double *y, const int pointNb);
    Approximation(const double *x,const double *y);

    // Destructor
    virtual ~Approximation() {}

    virtual void CalculateCoeff(int *x, int *y, int pointNb, int polDegree);

    void SetFines(const double fines);

    // Return the total money owed by the student
    virtual double MoneyOwed() const;

private:
    // Private data
    std::string name_;
    double fines_;
    double fees_;
};

#endif


