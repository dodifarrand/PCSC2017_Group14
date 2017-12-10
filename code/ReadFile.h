//
// Created by Anouk Allenspach on 10.12.17.
//

#ifndef PCSC_PROJECT6_READFILE_H
#define PCSC_PROJECT6_READFILE_H

class ReadFile: public ReadInput
{
private:
    FILE * mpFile;

public:
    ReadFile();
    ReadFile(char const * file_name);
    FILE * GetFilePointer();


};

#endif //PCSC_PROJECT6_READFILE_H
