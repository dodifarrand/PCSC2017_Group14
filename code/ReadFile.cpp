//

#include <cstdio>
#include "ReadInput.h"
#include "ReadFile.h"



ReadFile::ReadFile() {
// read the file into the vectors
    char const * file_name = ReadInput::GetFileName();
    mpFile = fopen(file_name,"r");    // use file pointer

}
ReadFile::ReadFile(char const * file_name) {
// read the file into the vectors

    mpFile = fopen(file_name,"r");    // use file pointer

}

FILE * ReadFile::GetFilePointer() {
   // std::cout << mpFile << std::endl;
    return mpFile;
}