#ifndef TGAREADER_H
#define TGAREADER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <fstream>

class TGAReader
{
public:
    TGAReader();
    ~TGAReader();

    void tgaLoadFile(FILE *file);


private:
    int status;
    char type, pixDepth;
    short int width, length;
    char *imageData;
};

#endif // TGAREADER_H
