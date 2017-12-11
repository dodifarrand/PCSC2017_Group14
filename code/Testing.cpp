//
// Created by Anouk Allenspach on 10.12.17.
//
#include <string>

class Testing{
private:
    std::string myfunc_name;
    int m_a;    // beginning of interval
    int m_b;    // end of interval
    int N_points;   // number of points to generate
public:
    std::string GetFunctionName();
    void GetInterval();
    Testing();


};

Testing::Testing() {
    myfunc_name = GetFunctionName();
    GetInterval(m_a,m_b);

}
std::string Testing::GetFunctionName() {
    std::cout << "Enter a function you would like to approximate and press enter\n";
    std::string func_name;
    std::getline(std::cin, func_name);
    return func_name;
}

void Testing::GetInterval() {
    std::cout << "Enter the beginning of the interval"  << std::endl;
    int a;
    std::cin >> a;
    int b;
    std::cout << "Enter the end of the interval"  << std::endl;
    std::cin >> b;

    m_a = a;
    m_b = b;
}