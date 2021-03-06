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
    short int INTermediary;

    //Assign Memory
    cGarbage = (char*)malloc(2);
    infomove = (char*)malloc(2);

    ifstream TGAMAP;
    TGAMAP.open(File, ios::in|ios::binary);
    if(TGAMAP.is_open() == 1)
    {
    TGAMAP.seekg(0,ios::beg);
    //Read Header

    //Discard useless
    TGAMAP.read(cGarbage, 1);
    TGAMAP.read(cGarbage, 1);

    //Gets info and such
    infomove = &type;
    TGAMAP.read (infomove, 1);
    printf("Type=%d\n", type);

    TGAMAP.read(cGarbage, sizeof(short int));
    TGAMAP.read(cGarbage, sizeof(short int));
    TGAMAP.read(cGarbage, 1);
    TGAMAP.read(cGarbage, sizeof(short int));
    TGAMAP.read(cGarbage, sizeof(short int));

    infomove = (char*)&INTermediary;
    TGAMAP.read(infomove, sizeof(short int));
    width = INTermediary;
    infomove = (char*)&INTermediary;
    TGAMAP.read(infomove, sizeof(short int));
    length = INTermediary;
    infomove = (char*)&INTermediary;
    TGAMAP.read(infomove, 1);
    pixDepth = INTermediary;

    TGAMAP.read(cGarbage, 1);

    //Debug shit
    printf("width is %d\n", width);
    printf("length is %d\n", length);
    printf("pixdepth is %d\n", pixDepth);

    if (pixDepth > 8)
    {
        printf("Err: Not Grayscale\n");
        return(NULL);
    }

    //Load Image Pixels
    //Mode is # components per pixel
    int mode;
    int total;

    //Set mode
    mode = pixDepth / 8;

    //Calculate data to read
    total = length * width * mode;

    //Assign Read Memory
    imageData = (char*)malloc(total);

    //Load bits into imageData
    TGAMAP.read(imageData, total);
    return(imageData);
    }
    else
    {
        printf("Failed to open file");
        return(NULL);
    }
}

int TGAReader::getwidth()
{
    return(width);
}

int TGAReader::getlength()
{
    return(length);
}
