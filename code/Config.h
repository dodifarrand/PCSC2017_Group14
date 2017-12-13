//
// Created by Anouk Allenspach on 11.12.17.
//

#ifndef PCSC_PROJECT6_CONFIG_H
#define PCSC_PROJECT6_CONFIG_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class Config : public
{
private:
    char const* mfile_name; // file name of the configuration file
    int degree;
    std::string file_name_points; // file name of the file containing the points
    std::string type;
public:
    Config();
    Config(std::string f_name);
    std::string GetFileName();
    void ReadConfig();
    int GetDegree();
    std::string GetType();

};
#endif //PCSC_PROJECT6_CONFIG_H
