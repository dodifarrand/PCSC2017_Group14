/*
 * @file
 * Approximation.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: Created by Rodolphe
     *  implementation of Approximation class to approximate data points according to different methods
 */
#include "Approximation.hpp"
#include "Points.hpp"
#include <Eigen/Dense>
#include "Error.hpp"
#include <iostream>     // std::cout, std::fixed
#include <iomanip>
using namespace Eigen;


Approximation::Approximation(Points P){

this->x = P.m_x;
this->y = P.m_y;
this->nbPoint = P.m_nbPoint;
this->degree = P.m_degree;
this->type = P.m_type;
}
// base method to compute the coefficients for different types of methods
VectorXd Approximation::CalculateCoeff(){
     // Exceptions
     if(degree>nbPoint){
         throw ErrorHighDegreeType();
     }
     if(degree<0){
         throw ErrorNegDegreeType();
     }
     // vectors storing what will go into matrix
    double val [2*degree+1];
    double val2 [degree+1];

    // matrix A and vector b (Ax=b)
    MatrixXd A(degree+1,degree+1);
    VectorXd b(degree+1);

    // fill vector that will be A (val) and b (val2)
    for(int n = 0; n<2*degree+1;n++) {
        val[n] = 0;
        if(n<degree+1){
            val2[n] = 0;
        }
    }
    for(int n = 0; n<2*degree+1;n++){
        for(int i = 0; i<nbPoint;i++){
            val[n]+=pow(x[i],2*degree-n);
            if(n<degree+1){
                val2[n] += pow(x[i],degree-n)*y[i];
            }
        }
    }
    // put values in matrix A and vector b
    for(int i = 0; i<degree+1;i++){
        for(int j = 0; j<degree+1;j++){
            int n = i+j;
            A(i,j)=val[n];
        }
        b(i)=val2[i];
    }
    // solve Ax = b
    VectorXd a = A.fullPivLu().solve(b);

    // return solution
    return a;
}

// method to print the solution found
void Approximation::printSolution(VectorXd a){
    int len = a.size();
    std::cout<<"The polynomial has the following form: \n";
    std::cout<<"f(x) =  ";
    for(int i = 0; i<len;i++){
        if(i==0) {
            std::cout<< std::setprecision(3) << a(len - 1 - i) << " + ";
        }
        else if(i==len-1){
            std::cout << std::setprecision(3)  << a(len - 1 - i) << "x^"<<i<<std::endl;
        }
        else {
            std::cout << std::setprecision(3)  << a(len - 1 - i) << "x^"<<i<<" + ";
        }
    }
}
double Approximation::CalculateError(VectorXd a){
    // initialize err and pointer to double fx
    double err = 0;
    double fx[nbPoint];
    // intialize fx
    for(int i = 0; i<nbPoint;i++) {
        fx[i] = 0;
    }
    // compute fx
    for(int i = 0; i<nbPoint;i++){
        fx[i] = 0;
        for(int j = 0; j<degree+1;j++){
            fx[i] += pow(x[i],degree-j)*a(j);   // a(j) is the coeff  for x^(degree-j), x[i] is the x coordinate of point i
        }
        err += pow(y[i]-fx[i],2);   // increment error
    }

    std::cout<< "The error is : " << err << std::endl;
    // return the error
    return err;
}


/*********************** Fitting ***********************/
/**
* This is the implementation of the (data) Fitting class
*/
VectorXd Fitting::CalculateCoeff() {
    VectorXd a = Approximation::CalculateCoeff();
    return a;
};

// method to compute error of approximation
double Fitting::CalculateError(VectorXd a) {
    double err = Approximation::CalculateError(a);
    return err;
}

// method to print the solution
void Fitting::printSolution(VectorXd a){
    Approximation::printSolution(a);

}

/*********************** Interpolation ***********************/
/**
* This is the implementation of the (data) Interpolation class
*/
// method to chose which method to use according to the degree and the number of points
VectorXd Interpolation::CalculateCoeff() {
    if (degree<nbPoint-1){
        throw ErrorDegreeTypeType();
    }
    VectorXd a = Approximation::CalculateCoeff();
    return a;
}

// Print solution for the interpolation
void Interpolation::printSolution(VectorXd a) {
    Approximation::printSolution(a);
}

//Calculate error for the interpolation
double Interpolation::CalculateError(VectorXd a) {
    double err = Approximation::CalculateError(a);
    if(err>10){
        throw ErrorPointsType();
    }
    // add exceptions for the error too big
    return err;
}


/*********************** Piece-wise ***********************/
/**
* This is the implementation of the piecewise class
*/
// method that determine the coeff depending on the type
VectorXd PieceWiseInterpolation::CalculateCoeff() {
    // Exceptions
    if(degree>=nbPoint){
        throw ErrorHighDegreeType();
    }
    if(degree<0){
        throw ErrorNegDegreeType();
    }
    VectorXd a;
    if(type == "PiecewiseContinuous"){
        a = PieceWiseInterpolation::PieceWiseContinuous();
    }
    else {
        a = PieceWiseInterpolation::PieceWise();
    }
    return a;
}

// method that determines the coeff for a piecewise
VectorXd PieceWiseInterpolation::PieceWise() {
    // initialization
    std::cout << "Piecewise in DataInterpolation Class " << std::endl;
    int funcNb, resDegree, unknownNb;

    // number of funtions to compute with the given degree
    funcNb = floor((nbPoint - 1) / degree);

    // degree of the polynom that if left over
    resDegree = (nbPoint) - (funcNb*degree+1);

    // find number of coefficients to compute
    if (resDegree > 0) {
        unknownNb = funcNb * (degree + 1) + resDegree + 1;
    } else {
        unknownNb = funcNb * (degree + 1);
    }


    // initialization of solution vector to zero
    VectorXd a(unknownNb);
    for (int i = 0; i < unknownNb; i++) {
        a(i) = 0;
    }

    int f = 0;

    // group points in auxiliary vectors
    double x_p[degree + 1];
    double y_p[degree + 1];
    for(int i=0;i<degree+1;i++){
        x_p[i]=0;
        y_p[i]=0;
    }
    for (int i = 0; i < funcNb; i++) {
        for (int j = 0; j < degree + 1; j++) {
            x_p[j] = x[i * (degree) + j];
            y_p[j] = y[i * (degree) + j];
            //cout << xi[j] << " & " << yi[j] << endl;
        }

        // object point to create object datafinterpolation
        Points P(x_p, y_p, degree + 1, degree);
        Interpolation di(P);

        // compute coefficients for current function
        VectorXd coeff = di.CalculateCoeff();
        for (int j = 0; j < degree + 1; j++) {
            a(f + j) = coeff(j);    // add to final vector
        }
        f = f + degree + 1;
        //   cout << " new " << endl;
    }

    // do the same thing as above for a degree smaller than the degree specified by the user
    if (resDegree > 0) {
        double xi2[resDegree + 1];
        double yi2[resDegree + 1];
        for (int j = 0; j < resDegree + 1; j++) {
            xi2[j] = 0;
            yi2[j] = 0;
        }
        for (int j = 0; j < resDegree + 1; j++) {
            xi2[j] = x[funcNb * (degree) + j];
            yi2[j] = y[funcNb * (degree) + j];
            //     cout << xi2[j] << " & " << yi2[j] << endl;
        }

        // object point to generate object DataInterpolation
        Points P2(xi2, yi2, resDegree+ 1, resDegree);
        Interpolation di2(P2);

        // compute the coefficients for the remaining points
        VectorXd coeff2 = di2.CalculateCoeff();

        // fill coefficients in vector to be returned
        for (int j = 0; j < resDegree + 1; j++) {
            a(f + j) = coeff2(j);
        }
    }

    // return coefficients
    return a;
}
/**
* This is the implementation of the piecewise interpolation class
*/
// method that determine the coeff for a piecewise continuous
VectorXd PieceWiseInterpolation::PieceWiseContinuous(){
    if(degree>3){
        throw ErrorDegreeTypeType();
    }
    std::cout << "Piecewise Cont in DataInterpolation Class " << std::endl;
    // set the number of points to the required value
    int unknownNb = (nbPoint-1)*(degree+1);

    // initialize matrix A and b
    MatrixXd A(unknownNb,unknownNb);
    VectorXd b(unknownNb);

    // fill a and b with zeros
    for(int i = 0;i<unknownNb;i++){
        for(int j = 0;j<unknownNb;j++){
            A(i,j)=0;
        }
        b(i)=0;
    }
    // initialize j and f
    int j = 0;
    int f = 0;

    // initialize vector to contain coefficients
    VectorXd a(unknownNb);

    // according to the degree, do
    switch(degree){
        case 1: {
            for (int i = 0; i<unknownNb;i=i+2){
                a(i)= (y[j+1]-y[j])/(x[j+1]-x[j]);
                a(i+1)= y[j]-x[j]*(y[j+1]-y[j])/(x[j+1]-x[j]);
                j+=1;
            }
            break;
        }
        case 2:{
            for(int i = 0;i<(nbPoint-1)*2;i = i+2){
                A(i,j) = pow(x[f],2);
                A(i,j+1) = pow(x[f],1);
                A(i,j+2) = pow(x[f],0);
                A(i+1,j) = pow(x[f+1],2);
                A(i+1,j+1) = pow(x[f+1],1);
                A(i+1,j+2) = pow(x[f+1],0);
                b(i)=y[f];
                b(i+1)=y[f+1];
                j = j+3;
                f = f+1;
            }
            A((nbPoint-1)*2,0)=1;
            j = 0;
            f = 1;
            for(int i = (nbPoint-1)*2+1;i<(unknownNb);i++) {
                A(i, j) = 2 * x[f];
                A(i, j + 1) = 1;
                A(i, j + 3) = -2 * x[f];
                A(i, j + 4) = -1;
                j = j + 3;
                f = f + 1;
            }
            a =  A.fullPivLu().solve(b);
            break;
        }
        case 3:{
            for(int i = 0;i<(nbPoint-1)*2;i = i+2){
                A(i,j) = pow(x[f],3);
                A(i,j+1) = pow(x[f],2);
                A(i,j+2) = pow(x[f],1);
                A(i,j+3) = pow(x[f],0);
                A(i+1,j) = pow(x[f+1],3);
                A(i+1,j+1) = pow(x[f+1],2);
                A(i+1,j+2) = pow(x[f+1],1);
                A(i+1,j+3) = pow(x[f+1],0);
                b(i)=y[f];
                b(i+1)=y[f+1];
                j = j+4;
                f = f+1;
            }
            j = 0;
            f = 1;
            for(int i = (nbPoint-1)*2;i<3*nbPoint-4;i++){
                A(i,j)=3*pow(x[f],2);
                A(i,j+1)=2*x[f];
                A(i,j+2)=1;
                A(i,j+4)=-3*pow(x[f],2);
                A(i,j+5)=-2*x[f];
                A(i,j+6)=-1;
                j = j+4;
                f = f+1;
            }
            j = 0;
            f = 1;
            for(int i = 3*nbPoint-4;i<4*nbPoint-6;i++){
                A(i,j)=6*x[f];
                A(i,j+1)=2;
                A(i,j+4)=-6*x[f];
                A(i,j+5)=-2;
                j = j+4;
                f = f+1;
            }
            j = 0;
            f = 0;
            for(int i = 4*nbPoint-6;i<unknownNb;i++){
                A(i,j)=6*x[f];
                A(i,j+1)=2;
                j = j+4*(nbPoint-2);
                f = f+nbPoint-1;
            }
            // compute solution to equation Ax = b
            a =  A.fullPivLu().solve(b);
            break;
        }
    }
    return a;
}

//Calculate error for the interpolation
double PieceWiseInterpolation::CalculateError(VectorXd a) {
    double err = 0;
    double fx[nbPoint];
    if (type == "PiecewiseContinuous") {
        int f = 0;
        // intialize fx
        for (int i = 0; i < nbPoint; i++) {
            fx[i] = 0;
        }
        for (int i = 0; i < nbPoint; i++) {
            if ((i-1)>0) {
                f = f + 1;
            }
            for (int j = 0; j < degree + 1; j++) {
                fx[i] += pow(x[i], degree - j) * a(j + (degree + 1) * f);   // a(j) is the coeff  for x^(degree-j), x[i] is the x coordinate of point i
            }

            err += pow(y[i] - fx[i], 2);   // increment error
        }
    } else {
        int funcNb, resDegree;
        int f = 0;
        funcNb = floor((nbPoint - 1) / degree);
        resDegree = (nbPoint) - (funcNb * degree + 1);
        for (int i = 0; i < nbPoint; i++) {
            fx[i] = 0;
        }
        std::cout << "The polynomials has the following form: \n";
        for (int i = 0; i < nbPoint; i++) {
            if (i < degree * funcNb + 1) {
                if ((i - 1) % degree == 0 and (i-1)>0) {
                    f = f + 1;
                }
                for (int j = 0; j < degree + 1; j++) {
                    fx[i] += pow(x[i], degree - j) * a(j + (degree + 1) * f);   // a(j) is the coeff  for x^(degree-j), x[i] is the x coordinate of point i
                }
            } else {
                for (int j = 0; j < resDegree + 1; j++) {
                    fx[i] += pow(x[i], resDegree - j) * a(a.size()-1-(resDegree)+j);   // a(j) is the coeff  for x^(degree-j), x[i] is the x coordinate of point i
                }
            }
            err += pow(y[i] - fx[i], 2);
        }
    }
    std::cout<< "The error is : " << err << std::endl;
    return err;
}

// Print solution for the interpolation
void PieceWiseInterpolation::printSolution(VectorXd a) {
    int iter, len, corr;
    corr = 0;
    if (type == "PiecewiseContinuous") {
        iter = nbPoint - 1;
        std::cout << "The polynomials has the following form: \n";
        for (int i = 1; i < iter + 1; i++) {
            len = degree;
            std::cout << "f" << i << "(x) =  ";
            for (int j = 0; j < len + 1; j++) {
                if (j == 0) {
                    std::cout << a((degree + 1) * (i) - 1 - j) << " + ";
                } else if (j == len) {
                    std::cout << a((degree + 1) * (i) - 1 - j) << "x^" << j << std::endl;
                } else {
                    std::cout << a((degree + 1) * (i) - 1 - j) << "x^" << j << " + ";
                }
            }
        }
    } else {
        if (((nbPoint - 1) % degree) == 0) {
            iter = ((nbPoint - 1) / degree);
        } else {
            iter = ((nbPoint - 1) / degree) + 1;
        }
        std::cout << "The polynomials has the following form: \n";
        for (int i = 1; i < iter + 1; i++) {
            if (i == iter) {
                len = a.size() - (iter - 1) * (degree + 1);
                corr = -(degree + 1) + len;
            } else {
                len = degree + 1;
            }
            std::cout << "f" << i << "(x) =  ";
            for (int j = 0; j < len; j++) {
                if (j == 0) {
                    std::cout << a((degree + 1) * (i) + corr - 1 - j) << " + ";
                } else if (j == len - 1) {
                    std::cout << a((degree + 1) * (i) + corr - 1 - j) << "x^" << j << std::endl;
                } else {
                    std::cout << a((degree + 1) * (i) + corr - 1 - j) << "x^" << j << " + ";
                }
            }
        }
    }
}





