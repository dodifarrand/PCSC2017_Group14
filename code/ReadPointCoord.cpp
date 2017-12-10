
#include "ReadFile.h"
#include <iostream>
#include "ReadPointCoord.h"
#include <cassert>

ReadPointCoord::ReadPointCoord() {
    mnPoints = GetNLines();
    assert(mnPoints > 0);
    m_x = new double[mnPoints];
    m_y = new double[mnPoints];

    for (int i=0; i<mnPoints; i++)
    {
        m_x[i] = 0.0;
        m_y[i] = 0.0;
    }

}


ReadPointCoord::~ReadPointCoord() {
  //  std::cout << "Destruct ReadPointCoord" << std::endl;
    delete[] m_x;
    delete[] m_y;
}

void ReadPointCoord::ReadData(){
    //std::cout << "ReadData" << std::endl;
    //FILE * pFile = GetFilePointer();
    float g1=0;
    float g2=0;
    for (int i = 0; i < mnPoints; i++) {

        fscanf(GetFilePointer(), "%g,%g", &g1, &g2);
        m_x[i] = (double)g1;
        m_y[i] = (double)g2;
        std::cout << "x[" << i << "]" << ": " << m_x[i] << ", y[" << i << "]: " <<  m_y[i] << std::endl;

    }

}