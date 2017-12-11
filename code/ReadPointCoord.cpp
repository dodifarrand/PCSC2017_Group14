
#include "Config.h"
#include <cassert>
#include "ReadPointCoord.h"


ReadPointCoord::ReadPointCoord() {

    std::string f_name = "data.csv";
    char const* p_file = f_name.c_str();
    file_name = p_file;
    m_x = new double;
    m_y = new double;
    mnPoints = 0;

}
ReadPointCoord::ReadPointCoord(char const* a_file_name) {
    file_name = a_file_name;
    std::cout << file_name << std::endl;
    CountLines();
    m_x = new double[mnPoints];
    m_y = new double[mnPoints];
    ReadData();
}


ReadPointCoord::~ReadPointCoord() {
  //  std::cout << "Destruct ReadPointCoord" << std::endl;
    delete[] m_x;
    delete[] m_y;
}

void ReadPointCoord::ReadData(){
    FILE* pFile = fopen(file_name,"r");
    float g1=0;
    float g2=0;

    for (int i = 0; i < mnPoints; i++) {

        fscanf(pFile, "%g,%g", &g1, &g2);
        m_x[i] = (double)g1;
        m_y[i] = (double)g2;
    }

}


double* ReadPointCoord::x(){
    return m_x;

}
double* ReadPointCoord::y(){
    return m_y;
}

void ReadPointCoord::CountLines() {
    std::ifstream read_file(file_name);
   // std::cout << "Count Lines" << std::endl;

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
        mnPoints = i;
    }

}

int ReadPointCoord::GetNPoints(){
    return mnPoints;
}