// main file to use classes

#include "ReadInput.h"
#include <iostream>
#include "ReadFile.h"
#include "ReadPointCoord.h"


int main(int argc, char* argv[]) {

    //ReadInput readInput;
    //readInput.GetNLines();
    //const char* file_name;
    //file_name = readInput.GetFileName();
    //std::cout << file_name << std::endl;
    //ReadFile readFile;
    //readFile.GetFilePointer();
    //readFile.GetNLines()

    ReadPointCoord readPoints;
    readPoints.ReadData();

 //   int nPoints = readPoints.GetNLines();
  //  std::cout << "Main number of points " << nPoints << std::endl;

    return 0;

}

