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

    fread(&cGarbage, sizeof(unsigned char), 1, file);
}
