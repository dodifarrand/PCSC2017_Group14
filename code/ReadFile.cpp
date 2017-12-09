//

#include <cstdio>
#include "ReadInput.h"


class ReadFile: public ReadInput
{
private:
    FILE * mpFile;

public:
    ReadFile();
    ReadFile(char const * file_name);
    FILE * GetFilePointer();


};

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
    return mpFile;
}


int main(int argc, char* argv[]) {

    ReadFile readFile;

    return 0;

}