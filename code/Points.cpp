
#include "Config.h"
#include <cassert>
#include "Points.hpp"

Points::Points(double *x, double *y, int nbPoint, int degree, std::string type){
    m_x = x;
    m_y = y;
    m_nbPoint = nbPoint;
    m_type = type;
    m_degree = degree;

}

Points::Points(std::string a_file_name){
    mfile_name = a_file_name.c_str();
    std::ifstream read_file(mfile_name);

    if(!read_file.is_open()) {
        std::cout << "Error opening file in read config." << std::endl;
    }

    std::string line;
    getline(read_file, line);
    std::istringstream ss(line);
    std::string token[3];
    int i = 0;
    while(std::getline(ss, token[i], ',')) {
        i++;
    }
    //std::string *tok = ReadConfig();
    data_file = token[0].c_str();
    //std::cout << data_file << std::endl;
    m_degree = atoi(token[1].c_str());
    m_type = token[2].c_str();
    CountLines(data_file);
    m_x = new double[m_nbPoint];
    m_y = new double[m_nbPoint];
    double** x = ReadData();
    for(int i = 0; i<m_nbPoint;i++){
        m_x[i] = x[i][1];
        m_y[i] = x[i][2];
    }

    std::cout<< m_x[3]<<std::endl;
}

double** Points::ReadData(){
    FILE* pFile = fopen(data_file,"r");
    float g1=0;
    float g2=0;
    double **x;
    x = new double*[m_nbPoint];
    for(int i = 0; i<m_nbPoint;i++){
        x[i] = new double[2];
    }
    for (int i = 0; i < m_nbPoint; i++) {
        fscanf(pFile, "%g,%g", &g1, &g2);
        x[i][1] = (double)g1;
        x[i][2] = (double)g2;
    }
    return x;
}


double* Points::x(){
    std::cout << m_x[3];
    return m_x;

}
double* Points::y(){
    return m_y;
}

int Points::CountLines(std::string data_file) {
    std::ifstream read_file(data_file);
    int *out = new int;
    if(!read_file.is_open()) {
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

std::string Points::GetType(){
    return m_type;
}

std::string* Points::ReadConfig() {
    std::ifstream read_file(mfile_name);

    if(!read_file.is_open()) {
        std::cout << "Error opening file in read config." << std::endl;
    }

    std::string line;
    getline(read_file, line);
    std::istringstream ss(line);
    std::string *token[3];
    int i = 0;
    while(std::getline(ss, *token[i], ',')) {
        i++;
    }
    //file_name_points = token[0].c_str();
    //degree = atoi(token[1].c_str()) ;
    //m_type = token[2].c_str();

    return *token;
}