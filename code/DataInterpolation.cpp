//
// Created by Anouk Allenspach on 13.12.17.
//

#include "DataInterpolation.h"
#include "DataFitting.h"

// method to chose which method to use according to the degree and the number of points
VectorXd DataInterpolation::CalculateCoeff() {
    // initialize solution vector containing the coefficients
    VectorXd a;

    // if the degree is inferior to the number of points minus one, do piecewise, otherwise do a polynomial approximation
    if(degree<nbPoint-1){
        a = PieceWise();
    }
    else {
        a = Polynomial();
    }
    // return the coefficients computed
    return a;
}

// method to do a polynomial approximation
VectorXd DataInterpolation::Polynomial() {

    // set the degree to the right value
    //degree = nbPoint -1;

    // initialize pointers to double vectors containing the computed values (for the matrix A and the vector b to solve Ax = b)
    double val [2*degree+1];
    double val2 [degree+1];

    // initialize matrix A and vector b
    MatrixXd A(degree+1,degree+1);
    VectorXd b(degree+1);

    // compute values of vectors that will be stored in A and b
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
    // fill matrix A and vector b
    for(int i = 0; i<degree+1;i++){
        for(int j = 0; j<degree+1;j++){
            A(i,j)=val[i+j];
        }
        b(i)=val2[i];
    }

    // solve the equation Ax = b
    VectorXd a =  A.fullPivLu().solve(b);

    // free memory

    // return the coefficients found
    return a;
}

// method to do a continuous piecewise approximation for degree <=3
VectorXd DataInterpolation::PieceWiseContinuous(){

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
            for(int i = 0;i<(degree-1)*2;i = i+2){
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
            for(int i = (nbPoint-1)*2+1;i<(unknownNb);i++){
                A(i,j)=2*x[f];
                A(i,j+1)=1;
                A(i,j+3)=-2*x[f];
                A(i,j+4)=-1;
                j = j+3;
                f = f+1;
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

VectorXd DataInterpolation::PieceWise() {
    // initialization
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
    double *xi = new double[degree + 1];
    double *yi = new double[degree + 1];
    for (int i = 0; i < funcNb; i++) {

        for (int j = 0; j < degree + 1; j++) {
            xi[j] = x[i * (degree) + j];
            yi[j] = y[i * (degree) + j];
            //cout << xi[j] << " & " << yi[j] << endl;
        }

        // object point to create object datafinterpolation
        Points P(xi, yi, degree + 1, degree);
        DataInterpolation df(P);

        // compute coefficients for current function
        VectorXd coeff = df.CalculateCoeff();
        for (int j = 0; j < degree + 1; j++) {
            a(f + j) = coeff(j);    // add to final vector
        }
        f = f + degree + 1;
     //   cout << " new " << endl;
    }
    delete[] xi;
    delete[] yi;

    // do the same thing as above for a degree smaller than the degree specified by the user
    if (resDegree > 0) {
        double *xi2 = new double[resDegree + 1];
        double *yi2 = new double[resDegree + 1];
        for (int j = 0; j < resDegree + 1; j++) {
            xi2[j] = x[funcNb * (degree) + j];
            yi2[j] = y[funcNb * (degree) + j];
       //     cout << xi2[j] << " & " << yi2[j] << endl;
        }

        // object point to generate object DataInterpolation
        Points P2(xi2, yi2, resDegree+ 1, resDegree);
        DataInterpolation df2(P2);

        // compute the coefficients for the remaining points
        VectorXd coeff2 = df2.CalculateCoeff();

        // fill coefficients in vector to be returned
        for (int j = 0; j < resDegree + 1; j++) {
            a(f + j) = coeff2(j);
        }
        delete[] xi2;
        delete[] yi2;
    }

    // return coefficients
    return a;
}

void DataInterpolation::printSolution(VectorXd a){
    // Print the solution depending on the type
    if(degree<nbPoint-1){
        int iter,len;
        if(((nbPoint - 1) % degree)==0){
            iter = ((nbPoint - 1) / degree);
        }else {
            iter = ((nbPoint - 1) / degree) + 1 ;
        }
        std::cout<<"The polynomials has the following form: \n";
        for(int i = 1;i<iter+1;i++){
            if(i==iter){
                len = a.size()-(iter-1)*(degree+1);
            }else{
                len = degree+1;
            }
            std::cout<<"f"<<i<<"(x) =  ";
            for(int j = 0; j<len;j++){
                if(j==0) {
                    std::cout << a((degree+1)*(i) - 1 - j) << " + ";
                }
                else if(j==len-1){
                    std::cout << a((degree+1)*(i) - 1 - j) << "x^"<<j<<std::endl;
                }
                else {
                    std::cout << a((degree+1)*(i) - 1 - j) << "x^"<<j<<" + ";
                }
            }
        }

    } else {
        //DataFitting::printSolution(a);
    }
}