#ifndef TGAREADER_H
#define TGAREADER_H


class TGAReader
{
    public:
        TGAReader(unsigned char id, unsigned char colmaptype, unsigned char imatype, short int colmapfirst,
                  short int colmaplength, short int mapentrysize, short int hozorigin, short int vertorigin,
                  short int width, short int height, unsigned char pixeldepth, unsigned char imgdescr);
        virtual ~TGAReader();
    protected:
    private:
};

#endif // TGAREADER_H
