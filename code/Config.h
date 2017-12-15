/**
 * @file
 * Config.h
 * 	This is our config class that reads the configuration file
 */

#ifndef PCSC_PROJECT6_CONFIG_H
#define PCSC_PROJECT6_CONFIG_H
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

class Config  {
private:
    char const* mfile_name; // /*!< file name of the configuration file */
    int degree; // /*!< degree of polynomial */
    std::string file_name_points; // /*!<file name of the file containing the points */
    std::string type; // /*!< type of approximation to do */
public:

    Config();
    Config(std::string f_name /**< [in] configuration file name. */);
    std::string GetFileName();
    void ReadConfig();
    int GetDegree();
    std::string GetType();
    //friend class Points;

};
#endif //PCSC_PROJECT6_CONFIG_H
