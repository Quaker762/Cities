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

char * TGAReader::tgaLoadFile(string File)
{
    char * cGarbage;
    char * infomove;
    char intermediary;

    ifstream TGAMAP;
    TGAMAP.open(File, ios::in|ios::binary);
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

    //Set mode
    mode = pixDepth / 8;

    //Calculate data to read
    total = length * width * mode;

    //Load bits into imageData
    TGAMAP.read (imageData, total);
    return(imageData);
}

int TGAReader::getwidth()
{
    return(width);
}

int TGAReader::getlength()
{
    return(length);
}
