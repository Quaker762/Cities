#include "../include/TGAReader.h"
#include <iostream>
#include <fstream>
using namespace std;

TGAReader::TGAReader()
{

}

TGAReader::~TGAReader()
{

}

void TGAReader::tgaLoadFile(FILE *file)
{
    char * cGarbage;
    char * infomove;
    char intermediary;

    ifstream TGAMAP;
    TGAMAP.open("Temp", ios::in|ios::binary);
    TGAMAP.seekg(0,ios::beg);
    //Read Header

    //Discard useless
    TGAMAP.read (cGarbage, 1);
    TGAMAP.read (cGarbage, 1);

    //Gets info and such
    infomove = &type;
    TGAMAP.read (infomove, 1);

    TGAMAP.read (cGarbage, sizeof(short int));
    TGAMAP.read (cGarbage, sizeof(short int));
    TGAMAP.read (cGarbage, 1);
    TGAMAP.read (cGarbage, sizeof(short int));
    TGAMAP.read (cGarbage, sizeof(short int));

    infomove = &intermediary;
    TGAMAP.read (infomove, sizeof(short int));
    width = (short int)intermediary;
    infomove = &intermediary;
    TGAMAP.read (infomove, sizeof(short int));
    length = (short int)intermediary;
    infomove = &intermediary;
    TGAMAP.read (infomove, 1);
    pixDepth = (short int)intermediary;

    TGAMAP.read (cGarbage, 1);

    //Load Image Pixels

    //Mode is # components per pixel
    int mode;
    int total;
    int i;
    int j;
    char aux;

    //Set mode
    mode = pixDepth /8;

    //Calculate data to read
    total = length * width * mode;

    //Load bits into imageData
    TGAMAP.read (imageData, total);

    //Generate Heights
    //Order is width -> length
    //Width is left to right
    //Length is top to bottom or vise versa
    char heightmap[1000][1000];
    for (i=0; i < width; i++)
    {
        for (j=0; j < length; j++)
        {
            heightmap[i][j] = imageData[i*width + j];
        }
    }

}
