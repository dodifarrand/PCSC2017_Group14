//
// Created by Anouk Allenspach on 10.12.17.
//
#include "FunctionApprox.h"

FunctionApprox::FunctionApprox() {

    std::cout << "FunctionApprox constructed without testing.csv file supplied" << std::endl;
    m_a = 0;
    m_b = 0;
    N_points = 0;
    SetFunctionPointer("blah");

}

FunctionApprox::FunctionApprox(std::string testing_file, double (*pf)(double) = NULL) {

    char const* mfile_name = testing_file.c_str();
    std::ifstream read_file(mfile_name);

    if(!read_file.is_open()) {
        std::cout << "Error opening file in read config." << std::endl;
    }

    std::string line;
    getline(read_file, line);
    std::istringstream ss(line);
    std::string token[6];
    int i = 0;
    while(std::getline(ss, token[i], ',')) {
        i++;
    }
    std::string myfunc_name = token[0]; // function name of user's function
    double a = atof(token[1].c_str());  /
    double b = atof(token[2].c_str());
    N_points = atoi(token[3].c_str());  // number of points to generate
   std::string type = token[4];
    int degree = atoi(token[5].c_str());
    read_file.close();

    SetInterval(a,b);
    SetFunctionPointer(myfunc_name);
    if (my_p_function==NULL){
        my_p_function = pf;
    }

    // write the configuration file
    std::string config_filename = "config"+type+".csv";
    std::ofstream write_output(config_filename);
    assert(write_output.is_open()); // check that the file is open
    std::string function_name = myfunc_name+".csv";

    write_output << function_name.c_str() << "," << degree << "," << type.c_str() << std::endl;

// ******************************************************************************************************
    write_output.close();
    WritePoints(myfunc_name);

    // tell the user where to find his configuration file
    std::cout << "Your configuration has been written to " << config_filename << std::endl;
}

// function to set the interval members
void FunctionApprox::SetInterval(double a, double b) {
    m_a = a;
    m_b = b;
}

// set the function pointer to compute the different points
void FunctionApprox::SetFunctionPointer(std::string func_name){

    if (func_name=="sin(x)"){
        my_p_function = &sin;
    }
    else if (func_name=="cos(x)"){
        my_p_function = &cos;
    }
    else if (func_name=="tan(x)"){
        my_p_function = &tan;
    }
    else if (func_name=="exp(x)"){
        my_p_function = &exp;
    }
    else if (func_name=="log(x)"){
        my_p_function = &log;
    }
    else{   // the user has specified his/her own function
        my_p_function = NULL;
    }


}

// compute and write the points to a file with the same name as the function (.csv)
void FunctionApprox::WritePoints(std::string func_name) {
    double steps = (m_b-m_a)/(N_points-1);
    double x[N_points];
    double y[N_points];
    for (int i = 0; i < N_points; i++){
        // try and catch if inf or -inf
        x[i] = m_a+i*steps;
        //   std::cout << x[i] << std::endl;
        y[i] = my_p_function(m_a+double(i)*steps);
        //  std::cout << y[i] << std::endl;

    }

    std::string function_name = func_name+".csv";
    std::ofstream write_output(function_name);
    assert(write_output.is_open());
    for (int i = 0; i < N_points-1; i++){
        write_output << x[i] << "," << y[i] << std::endl;

    }
    write_output << x[N_points-1] << "," << y[N_points-1];
// ******************************************************************************************************
    write_output.close();
    // tell the user where to find his point file
    std::cout << "Your points have been written to " << function_name << std::endl;
}
