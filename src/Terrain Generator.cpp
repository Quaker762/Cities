#include "Terrain Generator.h"
#include "TGAReader.h"

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
    //length = Mapget.getlength();
    //width = Mapget.getwidth();
    //printf("%d\n", width);
    //printf("%d", length);
    int i;
    int j;
    char aux;

 //   for (i=0; i < width; i++)
    for(i=0; i < 1000; i++)
    {
 //       for (j=0; j < length; j++)
        for (j=0; j < 1000; j++)
        {
            heightmap[i][j] = (unsigned char)imageData[i*width + j];
            printf("i=%d j=%d y=%d\n", i, j, heightmap[i][j]);
        }
    }
}

int TerrainGenerator::UpdateHeightMap()
{
    GLuint terrainDL;
	float startW,startL;
	int i,j,aux;

	// compute the initial point of the terrain on the XZ plane
	startW = 1000 / 2.0 - 1000;
	startL = - 1000 / 2.0 + 1000;

	// Create the id for the display list
	terrainDL = glGenLists(1);

	// create the display list
	glNewList(terrainDL,GL_COMPILE);

	// generate n-1 strips, where n = terrainGridLength
	// for each vertex test if colors and normals are enabled
	for (i = 0 ; i < 1000-1; i++)
    {
		glBegin(GL_TRIANGLE_STRIP);
		for (j = 0;j < 1000; j++)
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
