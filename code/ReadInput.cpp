//
// Created by Anouk Allenspach on 09.12.17.
//
#include <string>
#include <iostream>
#include <fstream>


// implement reading data from file class
// what we have:
// filename

class ReadInput{
private:
    int n_rows;
    const char* file_name;
public:
    ReadInput();
    ReadInput(std::string f_name);
    int GetNLines();

};
ReadInput::ReadInput() {


std::cout << "Enter filename and press enter\n";
std::string f_name;
std::getline(std::cin, f_name);

f_name = f_name + ".csv";
    file_name = f_name.c_str();

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

    if (line.compare("") != 0){
    i++;
    }

    }
    read_file.close();
    n_rows = i;
    // for the found number of rows
    std::cout << "Number of rows = " << i << "\n";
}

ReadInput::ReadInput(std::string f_name) {

    f_name = f_name + ".csv";
    file_name = f_name.c_str();

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

        if (line.compare("") != 0){
            i++;
        }

    }
    read_file.close();
    n_rows = i;

}

int ReadInput::GetNLines(){
    // for the found number of rows
    std::cout << "Number of rows = " << n_rows << "\n";
    return n_rows;
}

int main(int argc, char* argv[]) {

    ReadInput readInput("data");
    readInput.GetNLines();

}