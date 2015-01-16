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
            if (heightmap[i][j] == 255)
            {
                heightmap[i][j] = heightmap[i][j-1];
            }
            //printf("i=%d j=%d y=%d\n", i, j, heightmap[i][j]);
            //SDL_Delay(5);
        }
    }
}

void TerrainGenerator::GenerateHeightMap()
{
    int i;
    int j;
    int k;
    int w;
    int l;

    width = 1000;
    length = 1000;

//Set all heights to 0
    for (i = 0; i < width; i++)
    {
        for (j = 0; j < length; j++)
        {
            heightmap[i][j] = 0;
        }
    }

    for (k = 0; k < 3000; k++)
    {
        //Get a Line, raise one side, lower other
        w = width * sin(SDL_GetTicks());
        l = length * cos(SDL_GetTicks());
        if (w < 0)
        {
            w = w * -1;
        }
        if (l < 0)
        {
            l = l * -1;
        }
        if (w == 0)
        {
            w = 1;
        }
        printf("y = (%d / %d) * x + %d\n", l, w, l);
        for (i = 0; i < length; i++)
        {
            for (j = 0; j < width; j++)
            {
                if (j > ((i * (l / w)) + l))
                {
                    if (heightmap[i][j] < 255)
                    {
                        heightmap[i][j] = heightmap[i][j] + 1;
                    }
                }
                else if (j < ((i * (l / w)) + 1))
                {
                    if (heightmap[i][j] != 0)
                    {
                    heightmap[i][j] = heightmap[i][j] - 1;
                    }
                }
            }
            //printf("Quart 1 = %d, Quart 2 = %d, Quart 3 = %d, Quart 4 = %d \n", heightmap[i][length / 4], heightmap[i][length / 2], heightmap[i][3*length / 4], heightmap[i][length-1]);
        }
    }

}

void TerrainGenerator::ScaleHeightMap()
{
    printf("preScaled Width = %d\npreScaled Length = %d\n", width, length);
    int i,j;
    for (i=0; i < width; i++)
    {
        //printf("For i = %d width = %d\n", i, width);
        for (j=0; j < length; j++)
        {
            //scaledheightmap[i][j] = (0.5 * (sin(((((double)heightmap[i][j]) / 510) * PI))) * (double)heightmap[i][j]);
            if (j > 1)
            {
                if (scaledheightmap[i][j] == scaledheightmap[i][j-1])
                {
                    scaledheightmap[i][j] = scaledheightmap[i][j] + 1;
                }
                if (scaledheightmap[i][j] > scaledheightmap[i][j-1] && scaledheightmap[i][j-1] > scaledheightmap[i][j-2])
                {
                    scaledheightmap[i][j-1] = (scaledheightmap[i][j] - scaledheightmap[i][j-2]) / 2;
                }
                else if (scaledheightmap[i][j] < scaledheightmap[i][j-1] && scaledheightmap[i][j-1] > scaledheightmap[i][j-2])
                {
                    scaledheightmap[i][j-1] = (scaledheightmap[i][j] + scaledheightmap[i][j-2] + scaledheightmap[i][j-1]) / 3;
                }

            }
            //printf("Scaled x = %d, z = %d, y = %d\n",i,j,scaledheightmap[i][j]);
        }
    }
    printf("prevarScaled width = %d\nprevarScaled length = %d\n", width, length);
    scaled = 1;
    printf("Scaled width = %d\nScaled length = %d\n", width, length);
}

int TerrainGenerator::UpdateHeightMap(float xOffset, float yOffset, float zOffset)
{
    GLuint terrainDL;
	float startW,startL;
	int i,j,aux;

	printf("preStartW width = %d\npreStartL length = %d\n", width, length);

	// compute the initial point of the terrain on the XZ plane
	startW = (width / 2.0) - width;
	startL = (-length / 2.0) + length;

	// Create the id for the display list
	terrainDL = glGenLists(1);

	// create the display list
	glNewList(terrainDL,GL_COMPILE);

    printf("Updated Width = %d\nUpdated Length = %d\n", width, length);
    printf("scaled = %d\n", scaled);

	// generate n-1 strips, where n = terrainGridLength
	// for each vertex test if colors and normals are enabled
	for (j = 0 ; j < length-1; j++)
    {
		glBegin(GL_TRIANGLE_STRIP);
		for (i = 0; i < width; i++)
        {
            //Colour Vertex based on height
            if (heightmap[i][j] < 84)
            {
                glColor3f(0.05f, 0.2f, 0.8f);
            }
            else if (heightmap[i][j] < 85)
            {
                glColor3f(0.7f, 0.7f, 1.0f);
            }
            else if (heightmap[i][j] < 90)
            {
                glColor3f(0.7f, 1.0f, 0.1f);
            }
            else if (heightmap[i][j] > 240)
            {
                glColor3f(0.8f, 0.8f, 0.9f);
            }
            else if (heightmap[i][j] - heightmap[i][j] > 5 | heightmap[i+1][j] - heightmap[i][j] < -5)
            {
                glColor3f(0.7f, 0.3f, 0.5f);
            }
            else
            {
                if (tan(heightmap[i][j]) >= 0)
                {
                    glColor3f(tan(heightmap[i][j] / 330) * 0.4f, (0.7 * tan(heightmap[i][j] / 330) + 0.3) * 1.0f,tan(heightmap[i][j] / 330) * 0.1f);
                }
                else if (tan(heightmap[i][j]) < 0)
                {
                    glColor3f(-tan(heightmap[i][j] / 330) * 0.4f, (-0.7 * tan(heightmap[i][j] / 330) + 0.3) * 1.0f, -tan(heightmap[i][j] / 330) * 0.1f);
                }
            }

            //Render Vertex for scaled or unscaled heightmap
            if (scaled == 1)
            {
                glVertex3f(startW + i + xOffset, scaledheightmap[i][j] + yOffset, startL - (j) + zOffset);
            }
            else if (scaled == 0)
            {
                glVertex3f(startW + i + xOffset, heightmap[i][j] + yOffset, startL - (j) + zOffset);
            }

            //Colour Vertex for terrain height
            if (heightmap[i+1][j] < 84)
            {
                glColor3f(0.05f, 0.2f, 0.8f);
            }
            else if (heightmap[i][j] < 85)
            {
                glColor3f(0.7f, 0.7f, 1.0f);
            }
            else if (heightmap[i+1][j] < 90)
            {
                glColor3f(0.7f, 1.0f, 0.1f);
            }
            else if (heightmap[i+1][j] > 240)
            {
                glColor3f(0.8f, 0.8f, 0.9f);
            }
            else if (heightmap[i+1][j] - heightmap[i][j] > 5 | heightmap[i+1][j] - heightmap[i][j] < -5)
            {
                glColor3f(0.7f, 0.3f, 0.5f);
            }
            else
            {
                if (tan(heightmap[i][j]) >= 0)
                {
                    glColor3f(tan(heightmap[i][j] / 330) * 0.4f, (0.7 * tan(heightmap[i][j] / 330) + 0.3) * 1.0f,tan(heightmap[i][j] / 330) * 0.1f);
                }
                else if (tan(heightmap[i][j]) < 0)
                {
                    glColor3f(-tan(heightmap[i][j] / 330) * 0.4f, (-0.7 * tan(heightmap[i][j] / 330) + 0.3) * 1.0f, -tan(heightmap[i][j] / 330) * 0.1f);
                }
            }

            //Render Vertex based on scaled or unscaled heightmap
            if (scaled == 1)
            {
                glVertex3f(startW + i + xOffset, scaledheightmap[i][j+1] + yOffset, startL - (j+1) + zOffset);
            }
            else if (scaled ==0)
            {
                glVertex3f(startW + i + xOffset, heightmap[i][j+1] + yOffset, startL - (j+1) + zOffset);
            }
		}
		glEnd();
	}
	glEndList();

	// return the list index so that the application can use it
	return(terrainDL);
}
