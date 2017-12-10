//
// Created by Anouk Allenspach on 09.12.17.
//
#include <string>
#include <iostream>
#include <fstream>
#include "ReadInput.h"
#include <sstream>

// implement reading data from file class
// what we have:
// filename, number of points, piecewise or polynomial

ReadInput::ReadInput() {
    std::cout << "Enter filename and press enter\n";
    std::string f_name;
    std::getline(std::cin, f_name);
    f_name = f_name + ".csv";
    file_name = f_name.c_str();
    CountLines();
}

int ReadInput::GetNLines(){
    // for the found number of rows
 //   std::cout << "Number of rows = " << n_rows << "\n";
    return n_rows;
}


const char* ReadInput::GetFileName(){
  //  std::cout << file_name << std::endl;
    return file_name;

}


void ReadInput::ReadHeader(std::string line) {
    std::istringstream ss(line);
    std::string token[5];

    int i = 0;
    while(std::getline(ss, token[i], ',')) {
  //      std::cout << token[i] << '\n';
        i++;
    }
    nPoints = atoi(token[2].c_str()) ;
    test = atoi(token[4].c_str());
    piece = atoi(token[3].c_str());


}

void ReadInput::CountLines() {
    std::ifstream read_file(file_name);


    if(!read_file.is_open()) {
        std::cout << "Error opening file." << std::endl;
    }

    int i = 0;
// start of reading file, get number of lines
    while (!read_file.eof())
    {
        std::string line;
        getline(read_file, line);
        if (i==0){
            ReadHeader(line);
        }
        if (line.compare("") != 0){
            i++;
        }

    }
    read_file.close();
    n_rows = i;
}


int ReadInput::isPiecewise() {
    return piece;
}

int ReadInput::isTest() {
    return test;
}