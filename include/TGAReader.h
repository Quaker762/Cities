#ifndef TGAREADER_H
#define TGAREADER_H
#include <stdio.h>

class TGAReader
{
public:
    TGAReader();
    ~TGAReader();

    void tgaLoadHeader(FILE *file);
    void tgaLoadImageData(FILE* file);


private:
    int status;
    unsigned char type, pixDepth;
    short int width, height;
    unsigned char *imageData;
};

#endif // TGAREADER_H
