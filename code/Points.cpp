//
// Created by Anouk Allenspach on 13.12.17.
//
#include <fstream>
#include "Points.hpp"
#include <iostream>

Points::Points(){
    m_x = new double;    // /*!< x vector */
    m_y = new double;    // /*!< y vector */
    m_nbPoint = 0; // /*!< number of points */
    m_degree = 0;// /*!< degree */
}
Points::Points(double *x, double *y, int nbPoint, int degree/*, std::string type*/){
    this->m_x = x;
    this->m_y = y;
    this->m_nbPoint = nbPoint;
    this->m_degree = degree;
    //this->m_type = type;
}

Points::Points(std::string point_file) {
    m_nbPoint = CountLines(point_file);
    m_x = new double[m_nbPoint];    // /*!< x vector */
    m_y = new double[m_nbPoint];    // /*!< y vector */
    m_degree = GetDegree();// /*!< degree */
    char const* file_name = point_file.c_str();
    FILE* pFile = fopen(file_name,"r");
    float g1=0;
    float g2=0;

    for (int i = 0; i < m_nbPoint; i++) {

        fscanf(pFile, "%g,%g", &g1, &g2);
        m_x[i] = (double)g1;
        m_y[i] = (double)g2;
    }

}


int Points::CountLines(std::string file_name) {
    std::ifstream read_file(file_name);
    // std::cout << "Count Lines" << std::endl;
    int i = 0;
    if(!read_file.is_open()) {
        std::cout << "Error opening file: " << file_name << std::endl;
    }
    else{

        while (!read_file.eof())
        {
            std::string line;
            getline(read_file, line);
            if (line.compare("") != 0){
                i++;
            }
        }
        read_file.close();
        //    std::cout << "End of Count Lines, total number of lines in file: " << i <<std::endl;

    }
    return i;
}


double* Points::x(){
    return m_x;

}

double* Points::y(){
    return m_y;
}

int Points::GetNPoints(){
    return m_nbPoint;
}