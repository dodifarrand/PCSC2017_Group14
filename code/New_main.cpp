// main file to use classes

#include "ReadInput.h"
#include <iostream>


int main(int argc, char* argv[]) {

    ReadInput readInput("data");
    readInput.GetNLines();
    const char* file_name;
    file_name = readInput.GetFileName();
    std::cout << file_name << std::endl;

    return 0;

}

