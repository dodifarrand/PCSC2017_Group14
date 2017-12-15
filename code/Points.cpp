/*
 * @file
 * Points.cpp
 *
 *  Created on: Dec 10, 2017
 *      Author: Created by Anouk Allenspach
     *  implementation of Points class
 */
#include <cassert>
#include "Points.hpp"
#include "Error.hpp"

// constructor for points for known inputs (x and y, number of points, degree and type(optional))
Points::Points(double *x, double *y, int nbPoint, int degree, std::string type){
    m_x = x;
    m_y = y;
    m_nbPoint = nbPoint;
    m_type = type;
    m_degree = degree;

}

// read a configuration file and define the members according to the information in the configuration file
Points::Points(std::string a_file_name){
    mfile_name = a_file_name.c_str();
    std::ifstream read_file(mfile_name);
    if(!read_file.is_open()) {
        // make sure file to be read is open
        std::cout << "Error opening file in read config." << std::endl;
    }
    // get the line
    std::string line;
    getline(read_file, line);

    // TODO assert that the line is not empty
    std::istringstream ss(line);
    std::string token[3];
    int i = 0;
    // read the line and store the strings in a string vector token
    while(std::getline(ss, token[i], ',')) {
        i++;
    }
    data_file = token[0].c_str();
    m_degree = atoi(token[1].c_str());
    m_type = token[2].c_str();

    // count the lines in the data file
    CountLines(data_file);
    m_x = new double[m_nbPoint];
    m_y = new double[m_nbPoint];
    // read the data into the designated vectors
    ReadData();
}

void Points::ReadData(){
    FILE* pFile = fopen(data_file,"r"); // file pointer to file to be read
    float g1=0;
    float g2=0;
    // read the points
    for (int i = 0; i < m_nbPoint; i++) {
        fscanf(pFile, "%g,%g", &g1, &g2);
        this->m_x[i] = (double)g1;
        this->m_y[i] = (double)g2;
    }
}

// return the vector with x-coordinates
double* Points::x(){

    return m_x;

}
// return the vector storing the y coordinates
double* Points::y(){
    return m_y;
}

// count number of lines in the point file
int Points::CountLines(std::string data_file) {
    std::ifstream read_file(data_file);
    int *out = new int;
    if(!read_file.is_open()) {
        // assert that the file is open, otherwise end the programm
        std::cout << "Error opening file: " << data_file << std::endl;
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
            if (i==0){
                // empty point file!
                throw ErrorDataType();
            }
        }
        read_file.close();
        *out = i;   // store the number of lines counted in a variable

    }
    m_nbPoint = *out;
    return *out;

}

// return the number of points
int Points::GetNPoints(){
    return m_nbPoint;
}

// return the type of approximation to be done
std::string Points::GetType(){
    return m_type;
}
