//
// Created by Anouk Allenspach on 09.12.17.
//

#ifndef PCSC_PROJECT6_READINPUT_H
#define PCSC_PROJECT6_READINPUT_H

#include <string>
class ReadInput{
private:
    int n_rows;
    const char* file_name;
    int piece;
    int nPoints;
    int test;
public:
    ReadInput();
    int GetNLines();
    const char* GetFileName();
    void ReadHeader(std::string line);
    void CountLines();
    int isTest();
    int isPiecewise();
    //~ReadInput(); ?
};



#endif //PCSC_PROJECT6_READINPUT_H
