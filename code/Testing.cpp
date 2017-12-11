//
// Created by Anouk Allenspach on 10.12.17.
//
#include "Testing.h"

Testing::Testing() {
    myfunc_name = "";
    m_a = 0;
    m_b = 0;
    N_points = 0;
    type = "";



}

Testing::Testing(std::string testing_file) {
  //  std::cout << "Testing" << std::endl;
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
    myfunc_name = token[0];
    double a = atof(token[1].c_str());
    double b = atof(token[2].c_str());
    N_points = atoi(token[3].c_str());
    type = token[4].c_str();
    int degree = atoi(token[5].c_str());
    read_file.close();

    SetInterval(a,b);
    SetFunctionPointer(myfunc_name);


    std::ofstream write_output("config2.csv");
    assert(write_output.is_open());
    write_output << myfunc_name+".csv" << "," << degree << "," << type << std::endl;

// ******************************************************************************************************
    write_output.close();

}


void Testing::SetInterval(double a, double b) {
    m_a = a;
    m_b = b;
}

std::string Testing::GetFuncName() {
    return myfunc_name;
}


void Testing::SetFunctionPointer(std::string func_name){

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
    else{
        std::cout << "No matching function, please specify your own function" << std::endl;
    }


}

void Testing::WritePoints() {
    double steps = double((m_b-m_a))/(N_points-1);
    double x[N_points];
    double y[N_points];
    for (int i = 0; i < N_points; i++){
        x[i] = m_a+i*steps;
        //   std::cout << x[i] << std::endl;
        y[i] = my_p_function(m_a+double(i)*steps);
        //  std::cout << y[i] << std::endl;

    }

    std::ofstream write_output(myfunc_name+".csv");
    assert(write_output.is_open());
    for (int i = 0; i < N_points-1; i++){
        write_output << x[i] << "," << y[i] << std::endl;

    }
    write_output << x[N_points-1] << "," << y[N_points-1];
// ******************************************************************************************************
    write_output.close();
}