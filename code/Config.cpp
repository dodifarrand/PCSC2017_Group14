//
// Created by Anouk Allenspach on 11.12.17.
// class to read the configuration file named config.csv

// used as Approx approx("config.csv");

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class Config
{
private:
    char const* mfile_name; // file name of the configuration file
    int degree;
    char const* mfile_name_points; // file name of the file containing the points
    char const* type;
public:
    Config();
    Config(std::string f_name);
    char const* GetFileName();
    void ReadConfig();
    int GetDegree();
    char const* GetType();

};
Config::Config(){

    Config("config.csv"); // file name of the configuration file
}

Config::Config(std::string f_name) {
    mfile_name = f_name.c_str();
    ReadConfig();

}


void Config::ReadConfig() {
    std::ifstream read_file(mfile_name);

    if(!read_file.is_open()) {
        std::cout << "Error opening file." << std::endl;
    }

    std::string line;
    getline(read_file, line);
    std::istringstream ss(line);
    std::string token[3];
    int i = 0;
    while(std::getline(ss, token[i], ',')) {
   //     std::cout << token[i] << std::endl;
        i++;
    }
    mfile_name_points = token[0].c_str();
 //   std::cout << mfile_name_points << std::endl;
    degree = atoi(token[1].c_str()) ;
    type = token[2].c_str();

}
char const* Config::GetFileName() {
//    std::cout << mfile_name_points << std::endl;
    return mfile_name_points;
}

int Config::GetDegree() {
    return degree;
}

char const* Config::GetType() {
    return type;
}

int main(int argc, char* argv[]){
    Config config("config.csv");
//    std::cout << "File Name: " << std::endl;
    std::string point_file = config.GetFileName();
    std::cout << point_file.c_str() << std::endl;

    int degree;
    degree = config.GetDegree();
    std::cout << degree << std::endl;

    std::string type = config.GetType();
    std::cout << type.c_str() << std::endl;
    return 0;

}
