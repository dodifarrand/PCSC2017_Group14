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
public:
    ReadInput();
    ReadInput(std::string f_name);
    int GetNLines();

};



#endif //PCSC_PROJECT6_READINPUT_H
