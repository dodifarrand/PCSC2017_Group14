#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtod */
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

// needs to pass characters encountered to the parser
class Scanner
{

public:
    Scanner (char const * buffer); // initialize scanner to scan the buffer that is passed

// function to return a number if the token is a number
    double ANumber();

// function to return what kind of token the current token is

    void KindOfToken();
// function to get next token
    Token GetToken() const;



private:
    int pos_line;               // at what position the scanner currently looks
    Token token;                // the current token that will be evaluated by the parser
    char const * const line;  // constant pointer to the constant char line that is read (we will read only one function)
    // line[pos_line] is the next character being read

    // can also pass a number
    double number;
};

// initialization with line entered
Scanner::Scanner (char const * buffer) : line (buffer)  // set line to buffer when scanner object is constructed
                                                        // not possible to do otherwise because we cannot change a constant
{
    std::cout << "Scanner with \"" << line << "\""  << std::endl; // only way to include " in a string is to put a backslash
    pos_line = 0;   // initialize position that is currently looked at to zero
    KindOfToken();  // initializes the token to the first kind of token the first character read, evaluated by the parser
}
// a method to get the current token
Token Scanner::GetToken() const {
    std::cout << "GetToken Method " << token << std::endl;
    return token;
}
//  KindOfToken recognizes the first available token and positions the index pos_line past
// the recognized part of the line
void Scanner::KindOfToken() {
   // std::cout << line[pos_line] << std::endl;
    switch(line[pos_line])
    {
        std::cout << line[pos_line] << std::endl;
        case '\0'  :
            std::cout << "end of function" << std::endl;
            token = t_end;
            break;
        case '1' :
        case '2' :
        case '3' :
        case '4' :
        case '5' :
        case '6' :
        case '7' :
        case '8' :
        case '9' :
        case '0' :
            std::cout << "it is a number: " << line[pos_line] << std::endl;
            token = t_number;
            number = atoi(&line[pos_line]);
            while (std::isdigit (line[pos_line]))
                ++pos_line;
            break;

        case t_plus :
            std::cout << "+" << std::endl;
            token = t_plus;
            pos_line++;
            break;
        case t_minus :
            std::cout << "-" << std::endl;
            token = t_minus;
            pos_line++;
            break;
        case t_mult :
            std::cout << "*" << std::endl;
            token = t_mult;
            pos_line++;
            break;
        case t_div :
            std::cout << "/" << std::endl;
            token = t_div;
            pos_line++;
            break;
        case t_leftP :
            std::cout << "(" << std::endl;
            token = t_leftP;
            pos_line++;
            break;
        case t_rightP :
            std::cout << ")" << std::endl;
            token = t_rightP;
            pos_line++;
            break;
        case t_assign :
            std::cout << "=" << std::endl;
            token = t_assign;
            pos_line++;
            break;
        case t_symbol :
            std::cout << "a symbol was encountered" << std::endl;
            token = t_symbol;
            break;
        default:
            std::cout << "an error is encountered" << std::endl;
            token = t_error;
            break;
    }
}



// Parses the C-string str interpreting its content as a floating point number
// (according to the current locale) and returns its value as a double. If
// endptr is not a null pointer, the function also sets the value of endptr to
// point to the first character after the number.

double Scanner::ANumber() {
    std::cout << "A Number is called with " << number << std::endl;
    assert(token == t_number);
    return number;

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
    SymbolTable(){}; // should not be called by compiler implicitly, only when we really want a symbol table
    ~SymbolTable(){}; // destructor

    // function to return


};

// class to parse string containing the function
// this will be used by the scanner in order to parse the token
// the symbol table will be used by the parser in order to evaluate the
class Parser
{
public:
    // constructor
    Parser(Scanner &ScanScanner, SymbolTable &ST_table);   // when the parser is constructed, it needs access to the scanner and the symbol table
    // destructor
    ~Parser();

    // function to evaluate what is parsed should tell us if it was successful or not
    //
    int Eval();
private:
    Scanner &scanner;
    SymbolTable &symTable;



};
// define constructor
Parser::Parser(Scanner &ScanScanner, SymbolTable &ST_table)
        : scanner(ScanScanner), symTable(ST_table) {

    std::cout << "Create object of type parser "  << std::endl;
}

// define the destructor
Parser::~Parser() {
    std::cout << "Destroy the parser" << std::endl;
}

// define function to evaluate tokens
int Parser::Eval() {
    std::cout << "Eval Method is called" << std::endl;
    Token c_token = scanner.GetToken();
    std::cout << "evaluate the current token: " << c_token << std::endl;
    while (c_token!=t_end){  // while the current token is not an end token
        std::cout << "evaluate the current token: " << c_token << std::endl;
        switch (c_token)
        {

            case t_error:    // something unexpected
                return -1;

            case t_number :
                double n;
                n = scanner.ANumber();
                std::cout << "Number: " << n << std::endl;
                break;
             case t_plus :
                 std::cout << "Plus\n";
                 break;
            case t_minus :
                std::cout << "Minus\n";
                break;
            case t_mult :

                break;
            case t_div :

                break;
            case t_leftP :

                break;
            case t_rightP :

                break;
            case t_assign :

                break;
            case t_symbol :
                return -1;
        }
        return 1;
    }

    // after evaluating the tree we are done
}






int main(int argc, char* argv[]){
    const int maxBuf = 100; // maximum number of characters that can be entered

    char buffer [maxBuf];  // create the character vector that will store the different characters in function
    int status = 1;
    SymbolTable ST_Table;
    std::cout << "Enter a function "; // prompt
    std::cin.getline (buffer, maxBuf);
    while (status != -1)
        {

            Scanner Sscanner (buffer);          // pass the line read to the scanner
            Parser parser(Sscanner, ST_Table);  // create object parser to parse the line
            // here we evaluate what is in object parser
            status = parser.Eval ();
            std::cout << status << std::endl;
            status = -1;
        }  // in order to do the loop at least once

    // different tokens that can be encountered, note that this should be in the scanner class which assigns the right token
    // for a given character

    return 0;
}