#include "../include/Terrain Generator.h"
#include "../include/TGAReader.h"

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
    //Ensure to change array size if using map larger than 1000 x 1000
    int i,j,temp;
    for (i=0; i < width; i++)
    {
        for (j=0; j < length; j++)
        {
            temp = ((-30.0) / (heightmap[i][j] - 265.0) + 1) * heightmap[i][j];
            //printf("Temp = %d\n", temp);
            scaledheightmap[i][j] = temp * 1.0f;
            //printf("Scaled x = %d, z = %d, y = %f\n",i,j,scaledheightmap[i][j]);
        }
    }
    scaled = 1;
}

//ONLY CALL FOR SCALED TERRAIN
void TerrainGenerator::SmoothHeightMap(int advancedsmooth)
{
    int i, j;

    //Advanced Smoothing [WIP]
    if (advancedsmooth == 1)
    {
        for (i = 4; i < width; i++)
        {
            for (j = 0; j < length; j++)
            {
                if (scaledheightmap[i-3][j] == scaledheightmap[i-4][j] || scaledheightmap[i-3][j] == scaledheightmap[i-2][j])
                {
                    if (scaledheightmap[i][j] > scaledheightmap[i-3][j] || scaledheightmap[i][j] < scaledheightmap[i-3][j])
                    {
                        scaledheightmap[i-3][j] = ((scaledheightmap[i][j] - scaledheightmap[i-3][j]) * sin(PI / 8)) + scaledheightmap[i-3][j];
                        scaledheightmap[i-2][j] = ((scaledheightmap[i][j] - scaledheightmap[i-3][j]) * sin((2 * PI) / 8)) + scaledheightmap[i-3][j];
                        scaledheightmap[i-1][j] = ((scaledheightmap[i][j] - scaledheightmap[i-3][j]) * sin((3 * PI) / 8)) + scaledheightmap[i-3][j];
                        scaledheightmap[i][j] = ((scaledheightmap[i][j] - scaledheightmap[i-3][j]) * sin((4 * PI) / 8)) + scaledheightmap[i-3][j];
                    }
                }
            }
        }
        for (i = 0; i < width; i++)
        {
            for (j = 4; j < length; j++)
            {
                if (scaledheightmap[i][j-3] == scaledheightmap[i][j-4] || scaledheightmap[i][j-3] == scaledheightmap[i][j-2])
                {
                    if (scaledheightmap[i][j] > scaledheightmap[i][j-3] || scaledheightmap[i][j] < scaledheightmap[i][j-3])
                    {
                        scaledheightmap[i][j-3] = ((scaledheightmap[i][j] - scaledheightmap[i][j-3]) * sin(PI / 8)) + scaledheightmap[i][j-3];
                        scaledheightmap[i][j-2] = ((scaledheightmap[i][j] - scaledheightmap[i][j-3]) * sin((2 * PI) / 8)) + scaledheightmap[i][j-3];
                        scaledheightmap[i][j-1] = ((scaledheightmap[i][j] - scaledheightmap[i][j-3]) * sin((3 * PI) / 8)) + scaledheightmap[i][j-3];
                        scaledheightmap[i][j] = ((scaledheightmap[i][j] - scaledheightmap[i][j-3]) * sin((4 * PI) / 8)) + scaledheightmap[i][j-3];
                    }
                }
            }
        }
    }

    //Basic Smoothing
    for (i = 2; i < width; i++)
    {
        for (j = 2; j < length; j++)
        {
            scaledheightmap[i-1][j-1] = (scaledheightmap[i-2][j-1] + scaledheightmap[i-1][j-1] + scaledheightmap[i][j-1] + scaledheightmap[i-1][j-2] + scaledheightmap[i-1][j-1] + scaledheightmap[i-1][j] + scaledheightmap[i-2][j-2] + scaledheightmap[i-2][j] + scaledheightmap[i][j-2] + scaledheightmap[i][j]) * 0.1;
            //printf("Smoothed i = %d j = %d height = %f\n", i-1, j-1, scaledheightmap[i-1][j-1]);
        }
    }
}

int TerrainGenerator::UpdateHeightMap(float xOffset, float yOffset, float zOffset)
{
    GLuint terrainDL;
	float startW,startL;
	int i,j;

	printf("preStartW width = %d\npreStartL length = %d\n", width, length);

	// compute the initial point of the terrain on the XZ plane
	startW = (width / 2.0) - width; //Start = x = -500
	startL = (-length / 2.0) + length; //Start = z = 500

	// Create the id for the display list
	terrainDL = glGenLists(1);

	// create the display list
	glNewList(terrainDL,GL_COMPILE);

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
            else if (heightmap[i][j] - heightmap[i][j] > 2 || heightmap[i+1][j] - heightmap[i][j] < -2)
            {
                glColor3f(0.7f, 0.3f, 0.5f);
            }
            else if (heightmap[i][j+1] - heightmap[i][j] > 2 || heightmap[i][j+1] - heightmap[i][j] < -2)
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
            else if (heightmap[i+1][j] - heightmap[i][j] > 2 || heightmap[i+1][j] - heightmap[i][j] < -2)
            {
                glColor3f(0.7f, 0.3f, 0.5f);
            }
            else if (heightmap[i][j+1] - heightmap[i][j] > 2 || heightmap[i][j+1] - heightmap[i][j] < -2)
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

void TerrainGenerator::SaveHeightMap()
{
    ofstream SAVE ("map1.bin", ios::out | ios::trunc | ios::binary);
    if (SAVE.is_open())
    {
        int i, j, blocksize;
        float check;
        for (i = 0; i <= width; i++)
        {
            for (j = 0; j <= length; j++)
            {
                check = scaledheightmap[i][j];
                blocksize = sizeof(check);
                SAVE.write((char*)&check, blocksize);
            }
        }
    }
    else
    {
        printf("Error Openning File");
    }
    //De-Comment below to see that loading now works
/**    ifstream LOAD ("map1.bin", ios::in | ios::binary);
    if (LOAD.is_open())
    {
        int i, j;
        float check;
        for (i = 0; i <= width; i++)
        {
            for (j = 0; j <= length; j++)
            {
                LOAD.read((char*)&check, sizeof(float));
                printf("Original = %f\n", scaledheightmap[i][j]);
                printf("Retrievd = %f\n", check);
            }
        }
    }
    else
    {
        printf("Error Re-Openning File\n");
    } **/
}
/**
    We're doing some funky ass counting, so length array [2nd dimension] values are (z * -1) + 500,
    while the first dimension [x values] are (x + 500)
**/
int TerrainGenerator::GetHeightAtPoint(int x, int z)
{
    if (scaled == 0)
    {
        return heightmap[x + (width / 2)][(z * -1) + (length / 2)];
    }
    else if (scaled == 1)
    {
        return scaledheightmap[x + (width / 2)][(z * -1) + (length / 2)];
    }
    return -1;
}
