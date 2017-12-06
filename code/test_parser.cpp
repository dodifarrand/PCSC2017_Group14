
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
    Scanner (char const * buffer); // initialize scanner to scan the buffer that is passed
private:
    char const * const line;  // constant pointer to the constant char line that is read (we will read only one function)
};

Scanner::Scanner (char const * buffer) : line (buffer)  // set line to buffer when scanner object is constructed
                                                        // not possible to do otherwise because we cannot change a constant
{   // could also be empty
    std::cout << "Scanner with \"" << line << "\""  << std::endl; // only way to include " in a string is to put a backslash

}

// class to parse string containing the function
// this will be used by the scanner in order to parse the token
// the symbol table will be used by the parser in order to evaluate the
class Parser
{
public:
    // constructor
    Parser();
    // destructor
    ~Parser();

    // function to evaluate what is parsed should tell us if it was successful or not
    //
    int Eval();


};

Parser::Parser() {
    std::cout << "Create object of type parser" << std::endl;
}


Parser::~Parser() {
    std::cout << "Destroy the parser" << std::endl;
}

int Parser::Eval() {
    std::cout << "evaluate the tree" << std::endl;
    return -1;
}

// class of symbols to make the link between variable names and values
// In computing, a hash table (hash map) is a data structure which implements
// an associative array abstract data type, a structure that can map keys to
// values. A hash table uses a hash function to compute an index into an array
// of buckets or slots, from which the desired value can be found

class SymbolTable
{
public:
    // constructor
    SymbolTable(); // should not be called by compiler implicitly, only when we really want a symbol table
    ~SymbolTable(); // destructor


};





int main(int argc, char* argv[]){


    // different tokens that can be encountered
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