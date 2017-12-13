/**
 * @file
 * Config.cpp
 *
 *  Created on: Dec 13, 2017
 *      Author: Created by Anouk Allenspach
 *      class to read the configuration file named config.csv
 */




#include "Config.h"
/**
 * \brief Overridden default constructor for Config class
 */
Config::Config(){
    Config("config.csv"); // file name of the configuration file

}
/**
 * \brief Overridden default constructor taking the configuration file name as an input
 */
Config::Config(std::string f_name) {
    mfile_name = f_name.c_str();
    ReadConfig();

}

/**
 * \brief Method to read content of configuration file
 */
void Config::ReadConfig() {
    std::ifstream read_file(mfile_name);

    if(!read_file.is_open()) {
        std::cout << "Error opening file in read config." << std::endl;
    }

    std::string line;
    getline(read_file, line);
    std::istringstream ss(line);
    std::string token[3];
    int i = 0;
    while(std::getline(ss, token[i], ',')) {
        i++;
    }
    file_name_points = token[0].c_str();
    degree = atoi(token[1].c_str()) ;
    type = token[2].c_str();

}
/**
 * \brief Method to return the point file name
 */
std::string Config::GetFileName() {
    std::cout << file_name_points << std::endl;
    return file_name_points;
}
/**
 * \brief Method to return the degree to be used
 */
int Config::GetDegree() {
    return degree;
}

/**
 * \brief Method to return the type required
 */
std::string Config::GetType() {
    return type;
}


