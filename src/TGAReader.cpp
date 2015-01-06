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
    fread(type, sizeof(unsigned char), 1, file);

    fread(&iGarbage, sizeof(short int), 1, file);
    fread(&iGarbage, sizeof(short int), 1, file);
    fread(&cGarbage, sizeof(unsigned char), 1, file);
    fread(&iGarbage, sizeof(short int), 1, file);
    fread(&iGarbage, sizeof(short int), 1, file);

    fread(width, sizeof(short int), 1, file);
    fread(height, sizeof(short int), 1, file);
    fread(pixDepth, sizeof(unsigned char), 1, file);

    fread(&cGarbage, sizeof(unsigned char), 1, file);
}

//Loads image pixels, don't call directly
void tgaLoadImageData(FILE *file)
{
    //Mode is # components per pixel
    int mode;
    int total;
    int i;
    unsigned char aux;

    //Set mode
    mode = pixeldepth / 8;
    //Calculate amount of data to be read
    total = height * width * mode;
    //Load bits into imageData
    fread(imageData, sizeof(unsigned char), total, file);

    //Convert from BGR(A) to RGB(A) if image is coloured

    if (mode >= 3)
    {
        for (i=0; i < total; i+=mode)
        {
            aux = info->imageData[i];
            imageData[i] = info->imageData[i+2];
            imageData[i+2] = aux;
        }
    }
}

//Function to load image
void tgaInfo(char *filename)
{
    FILE *file;
    int mode, total;
    //Allocate Memory
    info = (tgaInfo *)malloc(sizeof(tgaInfo));
    if (info == NULL)
    {
        return(NULL);
    }
}
