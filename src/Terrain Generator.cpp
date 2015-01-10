#include "Terrain Generator.h"
#include "TGAReader.h"

#define PI 3.141592653589793238462643383279502884197169

TerrainGenerator::TerrainGenerator()
{
    //ctor
}

TerrainGenerator::~TerrainGenerator()
{
    //dtor
}

void TerrainGenerator::BuildHeightMap(string File)
{
    TGAReader Mapget;
    //Generate Heights
    //Order is width -> length
    //Width is left to right
    //Length is top to bottom or vise versa
    char * imageData = Mapget.tgaLoadFile(File);
    length = Mapget.getlength();
    width = Mapget.getwidth();
    printf("Map Width = %d\n", width);
    printf("Map Length = %d\n", length);
    int i;
    int j;
    char aux;

    for (i=0; i < width; i++)
    {
        for (j=0; j < length; j++)
        {
            heightmap[i][j] = (unsigned char)imageData[i*width + j];
            //printf("i=%d j=%d y=%d\n", i, j, heightmap[i][j]);
        }
    }
}

void TerrainGenerator::ScaleHeightMap()
{
    int i,j;
    for (i=0; i < width; i++)
    {
        for (j=0; j < length; j++)
        {
            scaledheightmap[i][j] = (4.70588 * (sin(((((double)heightmap[i][j]) / 510) * PI))) * (double)heightmap[i][j]) - 200;
            printf("Scaled x = %d, z = %d, y = %d\n",i,j,scaledheightmap[i][j]);
        }
    }
}

int TerrainGenerator::UpdateHeightMap()
{
    GLuint terrainDL;
	float startW,startL;
	int i,j,aux;

	// compute the initial point of the terrain on the XZ plane
	startW = width / 2.0 - width;
	startL = - length / 2.0 + length;

	// Create the id for the display list
	terrainDL = glGenLists(1);

	// create the display list
	glNewList(terrainDL,GL_COMPILE);

	// generate n-1 strips, where n = terrainGridLength
	// for each vertex test if colors and normals are enabled
	for (i = 0 ; i < width-1; i++)
    {
		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0;j < length; j++)
        {
            glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(startW + j, heightmap[i+1][j], startL - (i+1));
            glColor3f(1.0f, 1.0f, 1.0f);
			glVertex3f(startW + j, heightmap[i+1][j], startL - i);
		}
		glEnd();
	}
	glEndList();

	// return the list index so that the application can use it
	return(terrainDL);
}
