#ifndef TGAREADER_H
#define TGAREADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

class TGAReader
{
public:
    TGAReader();
    ~TGAReader();

    char * tgaLoadFile(std::string File);
    int getwidth();
    int getlength();


private:
    int status;
    char type, pixDepth;
    short int width, length;
    char *imageData;
};

#endif // TGAREADER_H
