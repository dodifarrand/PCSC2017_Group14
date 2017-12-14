
#include "Config.h"
#include <cassert>
#include "Points.hpp"
Points::Points(double *x, double *y, int nbPoint, int degree): m_degree(degree){
    m_x = x;
    m_y = y;
    m_nbPoint = nbPoint;

}

Points::Points(char const* a_file_name, int degree):m_degree(degree) {
    file_name = a_file_name;
    //  std::cout << file_name << std::endl;
    CountLines();
    m_x = new double[m_nbPoint];
    m_y = new double[m_nbPoint];
    ReadData();
}

void Points::ReadData(){
    FILE* pFile = fopen(file_name,"r");
    float g1=0;
    float g2=0;

    for (int i = 0; i < m_nbPoint; i++) {

        fscanf(pFile, "%g,%g", &g1, &g2);
        m_x[i] = (double)g1;
        m_y[i] = (double)g2;
    }

}


double* Points::x(){
    return m_x;

}
double* Points::y(){
    return m_y;
}

int Points::CountLines() {
    std::ifstream read_file(file_name);
    // std::cout << "Count Lines" << std::endl;
    int *out = new int;
    if(!read_file.is_open()) {
        std::cout << "Error opening file: " << file_name << std::endl;
    }
    else{
        int i = 0;
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
        *out = i;
    }

    m_nbPoint = *out;
    return *out;

}

int Points::GetNPoints(){
    return m_nbPoint;
}