#include "../include/TGAReader.h"

TGAReader::TGAReader()
{

}

TGAReader::~TGAReader()
{

}

void TGAReader::tgaLoadHeader(FILE *file)
{
    unsigned char cGarbage;
    short int iGarbage;

    //Discard un-needed info
    fread(&cGarbage, sizeof(unsigned char), 1, file);
    fread(&cGarbage, sizeof(unsigned char), 1, file);

    //Gets info (And discards garbage), type must be 2 or 3 (Uncompressed RBG(A) or Uncompressed Greyscale respectively)
    fread(&info->type, sizeof(unsigned char), 1, file);

    fread(&iGarbage, sizeof(short int), 1, file);
    fread(&iGarbage, sizeof(short int), 1, file);
    fread(&cGarbage, sizeof(unsigned char), 1, file);
    fread(&iGarbage, sizeof(short int), 1, file);
    fread(&iGarbage, sizeof(short int), 1, file);

    fread(&info->width, sizeof(short int), 1, file);
    fread(&info->height, sizeof(short int), 1, file);
    fread(&info->pixDepth, sizeof(unsigned char), 1, file);

    fread(&cGarbage, sizeof(unsigned char), 1, file);
}
