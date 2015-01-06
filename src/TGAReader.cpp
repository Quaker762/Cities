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

//Loads image pixels, don't call directly
void tgaLoadImageData(FILE *file)
{
    //Mode is # components per pixel
    int mode;
    int total;
    int i;
    unsigned char aux;

    //Set mode
    mode = info->pixeldepth / 8;
    //Calculate amount of data to be read
    total = info->height * info->width * mode;
    //Load bits into imageData
    fread(info->imageData, sizeof(unsigned char), total, file);

    //Convert from BGR(A) to RGB(A) if image is coloured

    if (mode >= 3)
    {
        for (i=0; i < total; i+=mode)
        {
            aux = info->imageData[i];
            info->imageData[i] = info->imageData[i+2];
            info->imageData[i+2] = aux;
        }
    }
}

//Function to load image
void tgaInfo(char *filename)
{
    FILE *file;
    tgaInfo *info;
    int mode, total;
    //Allocate Memory
    info = (tgaInfo *)malloc(sizeof(tgaInfo));
    if (info == NULL)
    {
        return(NULL);
    }
}
