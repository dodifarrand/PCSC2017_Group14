
#include <iostream>
#include <cassert>
// what could occur in a function
enum Token {
    t_end,      // end of function
    t_error,    // something unexpected
    t_number,   // a number
    t_plus,     // +
    t_minus,    // -
    t_mult,     // multiplication *
    t_div,      // division /
    t_leftP,    // (
    t_rightP,   // )
    t_assign,   // = (an assignment)
    t_symbol    // a symbol like cos or log
};
class Scanner
{
public:
    Scanner (char const * buf); // initialize scanner
private:
    char const * const buffer;
};

Scanner::Scanner (char const * buf) : buffer (buf)
{
    std::cout << "Scanner with \"" << buf << "\""  << std::endl; // only way to include " in a string is to put a backslash

}



class SymbolTable
{
public:
    // constructor
    explicit SymbolTable(int size); // should not be called by compiler implicitly, only when we really want a symbol table
    ~SymbolTable(); // destructor
    int

};
int main(int argc, char* argv[]){
    Token r;
    switch(r)
    {
        case t_end  :
            std::cout << "end of function" << std::endl;
            break;
        case t_error:
            std::cout << "error" << std::endl;
            break;
        case t_number :
            std::cout << "number" << std::endl;
            break;
        case t_plus :
            std::cout << "+" << std::endl;
            break;
        case t_minus :
            std::cout << "-" << std::endl;
            break;
        case t_mult :
            std::cout << "*" << std::endl;
            break;
        case t_div :
            std::cout << "/" << std::endl;
            break;
        case t_leftP :
            std::cout << "(" << std::endl;
            break;
        case t_rightP :
            std::cout << ")" << std::endl;
            break;
        case t_assign :
            std::cout << "=" << std::endl;
            break;
        case t_symbol :
            std::cout << "symbol" << std::endl;
            break;
    }
    return 0;
}