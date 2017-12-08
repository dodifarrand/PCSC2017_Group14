#include <iostream>
#include <fstream>
// read inputs from file

// just doubles
// Get info to be used by approx
// main: read file constructor(filename)
// data structure in points
// in approx: method takes point instance
// vector to evaluate the function

// read file: if in file cloud of points, we already know header: x, y ,

// read two files x and y, and x' where we want to evaluate the function
// generic approx: fitting inside check if your flag is poly, then you do poly, otherwise other














int main(int argc, char* argv[]) {

    // check if filename has been provided as a console input
    std::cout << "Number of command line arguments = " << argc << "\n";
    for (int i=0; i<argc; i++)
        {
         std::cout << "Argument " << i << " = " << argv[i];
         std::cout << "\n";
         }

    // 2 ways of providing file name: 1. through console input
    //  2. by providing file name as a console argument
    std::string f_name;
    const char* file_name;


    // ask for file name
    if (argc == 1){
        // only the program was called
        std::cout << "Enter the filename of your csv file and press enter\n";

        std::getline(std::cin, f_name);

        f_name = f_name + ".csv";
        file_name = f_name.c_str();
    }
        // file name was already provided
    else if (argc > 1){
        // program with filename was provided
        f_name = argv[1];
        file_name = f_name.c_str();
    }


    // now we have filename
    std::ifstream read_file(file_name);

    if (!read_file.is_open()) {
        std::cout << "Error opening file." << std::endl;
        return 1;
    }

    int i = 0;
    // start of reading file, get number of lines
    while (!read_file.eof()) {
        std::string line;
        getline(read_file, line);
        //std::cout << line[0];
        // std::cout << line << std::endl;
        if (line.compare("") != 0) {
            i++;
        }

    }


    // for the found number of rows
    std::cout << "Number of rows = " << i << "\n";
    read_file.close();
    int rows = i;

    // read the file into the vectors
    FILE *pFile = fopen(file_name, "r");    // use file pointer

    // what type are the values in the data file?
    std::cout << "Are your values integers or floats (press 1 for integers and 2 for double)?\n";
    int value_type;
    std::cin >> value_type;

    // adapt for case of double, maybe make a template
    switch (value_type){
        case 1: {
            int x[rows];
            int y[rows];

            // reset the read_file state
            read_file.clear();
            read_file.seekg(std::ios::beg);

            for (int i = 0; i < rows; i++) {

                fscanf(pFile, "%i,%i", &x[i], &y[i]);

                std::cout << "x[" << i << "]" << ": " << x[i] << ", y[" << i << "]: " << y[i] << std::endl;

            }
            read_file.close();
        }
        case 2: {
            double x[rows];
            double y[rows];

            // reset the read_file state
            read_file.clear();
            read_file.seekg(std::ios::beg);

            for (int i = 0; i < rows; i++) {

                fscanf(pFile, "%d,%d", &x[i], &y[i]);

                std::cout << "x[" << i << "]" << ": " << x[i] << ", y[" << i << "]: " << y[i] << std::endl;

            }
            read_file.close();
        }
    }
    // now we have the x and y vectors, two types int or double
    return 0;
}



