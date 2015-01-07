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

    ifstream TGAMAP;
    TGAMAP.open("Temp", ios::in|ios::binary);
    TGAMAP.seekg(0,ios::beg);
    //Read Header

    //Discard useless
    TGAMAP.read (cGarbage, sizeof(unsigned char));
    TGAMAP.read (cGarbage, sizeof(unsigned char));

    //Gets info and such
    infomove = &type;
    TGAMAP.read (infomove, sizeof(unsigned char));

    TGAMAP.read (cGarbage, sizeof(short int));
    TGAMAP.read (cGarbage, sizeof(short int));
    TGAMAP.read (cGarbage, sizeof(unsigned char));
    TGAMAP.read (cGarbage, sizeof(short int));
    TGAMAP.read (cGarbage, sizeof(short int));

    infomove = &width;
    TGAMAP.read (infomove, sizeof(short int));
    infomove = &height;
    TGAMAP.read (infomove, sizeof(short int));
    infomove = &pixdepth;
    TGAMAP.read (infomove, sizeof(unsigned char));

    TGAMAP.read (cGarbage, sizeof(unsigned char));
}

//Loads image pixels, don't call directly
//void tgaLoadImageData(FILE *file)
//{
    //Mode is # components per pixel
//    int mode;
//    int total;
//    int i;
//    unsigned char aux;

    //Set mode
//    mode = pixeldepth / 8;
    //Calculate amount of data to be read
//    total = height * width * mode;
    //Load bits into imageData
//    fread(imageData, sizeof(unsigned char), total, file);

    //Convert from BGR(A) to RGB(A) if image is coloured

 //   if (mode >= 3)
 //   {
 //       for (i=0; i < total; i+=mode)
 //       {
 //           aux = info->imageData[i];
 //           imageData[i] = info->imageData[i+2];
 //           imageData[i+2] = aux;
 //       }
 //   }
//}

//Function to load image
//void tgaInfo(char *filename)
//{
//    FILE *file;
//    int mode, total;
    //Allocate Memory
//    info = (tgaInfo *)malloc(sizeof(tgaInfo));
//    if (info == NULL)
//    {
//        return(NULL);
//    }
//}
