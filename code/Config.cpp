//
// Created by Anouk Allenspach on 11.12.17.
// class to read the configuration file named config.csv

// used as Approx approx("config.csv");

#include "Config.h"
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
        i++;
    }
    mfile_name_points = token[0].c_str();
    degree = atoi(token[1].c_str()) ;
    type = token[2].c_str();

}
std::string Config::GetFileName() {

    return mfile_name_points;
}

int Config::GetDegree() {
    return degree;
}

std::string Config::GetType() {
    return type;
}


