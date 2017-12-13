//
// Created by Anouk Allenspach on 13.12.17.
//
#include "Points.hpp"

Points::Points(double *x, double *y, int nbPoint, int degree/*, std::string type*/){
    this->m_x = x;
    this->m_y = y;
    this->m_nbPoint = nbPoint;
    this->m_degree = degree;
    //this->m_type = type;
}


