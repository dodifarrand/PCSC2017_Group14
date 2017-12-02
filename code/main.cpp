#include <iostream>
#include <fstream>
#include <iomanip>



int main(int argc, char* argv[]){


    std::cout << "Enter filename and press enter\n";
    std::string f_name;
    std::getline(std::cin, f_name);

    f_name = f_name + ".csv";
    const char* file_name = f_name.c_str();
    std::ifstream read_file(file_name);

    if(!read_file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return 1;
    }
    int i = 0;

    // start of reading file, get number of lines
    while (!read_file.eof())
    {
        std::string line;
        getline(read_file, line);
       // std::cout << line << std::endl;
        if (line.compare("") != 0){
            i++;
        }

    }


    // for the found number of rows
    std::cout << "Number of rows = " << i << "\n";
    read_file.close();
    int rows = i;

    // read the file into the vectors
    FILE * pFile = fopen(file_name,"r");

    // adapt for case of double, maybe make a template
    int x[rows];
    int y[rows];

    // reset the read_file state
    read_file.clear();
    read_file.seekg(std::ios::beg);

    for (int i = 0; i < rows; i++) {

            fscanf(pFile, "%i,%i", &x[i], &y[i]);
            std::cout << "x[" << i << "]" << ": " << x[i] << ", y[" << i << "]: " <<  y[i] << std::endl;

    }
    read_file.close();

    return 0;

}