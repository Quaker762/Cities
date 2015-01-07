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
    void tgaLoadImageData(FILE *file);


private:
    int status;
    unsigned char type, pixDepth;
    short int width, height;
    unsigned char *imageData;
};

#endif // TGAREADER_H
