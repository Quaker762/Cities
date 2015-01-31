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

int TerrainGenerator::RenderHeightMap(float xOffset, float yOffset, float zOffset, int xpos, int zpos)
{
    GLuint terrainDL;
	float startW,startL;
	int i,j,x,z;
	int startx, startz, endx, endz;

	// compute the initial point of the terrain on the XZ plane
	startW = (width / 2.0) - width; //Start = x = -500
	startL = (-length / 2.0) + length; //Start = z = 500
    z = 0;

    // Create the id for the display list
	terrainDL = glGenLists(1);

	// create the display list
	glNewList(terrainDL,GL_COMPILE);

    //Set start and end x and z positions for moving camera
	startx = (xpos - 254) + (width / 2);
        if (startx < 0)
        {
            startx = 0;
        }
        endx = (xpos + 255) + (width / 2);
        if (endx > width)
        {
            endx = width;
        }
        startz = ((zpos + 255) * -1) + (length / 2);
        if (startz < 0)
        {
            startz = 0;
        }
        endz = ((zpos - 254) * -1) + (length / 2);
        if (endz > length)
        {
            endz = length;
        }

	// generate n-1 strips, where n = terrainGridLength
	// for each vertex test if colors and normals are enabled
	for (j = startz ; j < endz - 1; j++)
    {
        //printf("Strip %d Started\n", z);
		glBegin(GL_TRIANGLE_STRIP);
		x = 0;
		for (i = startx; i < endx; i++)
        {
            //Colour Vertex based on height
            if (scaledheightmap[x][z] < 84)
            {
                glColor3f(0.05f, 0.2f, 0.8f);
            }
            else if (scaledheightmap[x][z] < 85)
            {
                glColor3f(0.7f, 0.7f, 1.0f);
            }
            else if (scaledheightmap[x][z] < 90)
            {
                glColor3f(0.7f, 1.0f, 0.1f);
            }
            else if (scaledheightmap[x][z] > 240)
            {
                glColor3f(0.8f, 0.8f, 0.9f);
            }
            else if (scaledheightmap[x][z] - scaledheightmap[x][z] > 2 || scaledheightmap[x+1][z] - scaledheightmap[x][z] < -2)
            {
                glColor3f(0.7f, 0.3f, 0.5f);
            }
            else if (scaledheightmap[x][z+1] - scaledheightmap[x][z] > 2 || scaledheightmap[x][z+1] - scaledheightmap[x][z] < -2)
            {
                glColor3f(0.7f, 0.3f, 0.5f);
            }
            else
            {
                glColor3f(0.4f, 1.0f, 0.1f);
            }

            //Render Vertex for scaled or unscaled heightmap
            if (scaled == 1)
            {
                //printf("Vertice %d - 1\n",x);
                glVertex3f(startW + i + xOffset, scaledheightmap[x][z] + yOffset, startL - (j) + zOffset);
            }
            else if (scaled == 0)
            {
                glVertex3f(startW + i + xOffset, heightmap[x][z] + yOffset, startL - (j) + zOffset);
            }

            //Colour Vertex for terrain height
            if (scaledheightmap[x+1][z] < 84)
            {
                glColor3f(0.05f, 0.2f, 0.8f);
            }
            else if (scaledheightmap[x][z] < 85)
            {
                glColor3f(0.7f, 0.7f, 1.0f);
            }
            else if (scaledheightmap[x+1][z] < 90)
            {
                glColor3f(0.7f, 1.0f, 0.1f);
            }
            else if (scaledheightmap[x+1][z] > 240)
            {
                glColor3f(0.8f, 0.8f, 0.9f);
            }
            else if (scaledheightmap[x+1][z] - scaledheightmap[x][z] > 2 || scaledheightmap[x+1][z] - scaledheightmap[x][z] < -2)
            {
                glColor3f(0.7f, 0.3f, 0.5f);
            }
            else if (scaledheightmap[x][z+1] - scaledheightmap[x][z] > 2 || scaledheightmap[x][z+1] - scaledheightmap[x][z] < -2)
            {
                glColor3f(0.7f, 0.3f, 0.5f);
            }
            else
            {
                glColor3f(0.4f, 1.0f, 0.1f);
            }

            //Render Vertex based on scaled or unscaled heightmap
            if (scaled == 1)
            {
                //printf("Vertice %d - 2\n",x);
                glVertex3f(startW + i + xOffset, scaledheightmap[x][z+1] + yOffset, startL - (j+1) + zOffset);
            }
            else if (scaled ==0)
            {
                glVertex3f(startW + i + xOffset, heightmap[x][z+1] + yOffset, startL - (j+1) + zOffset);
            }
            x = x+1;
		}
		z = z+1;
		glEnd();
		//printf("Strip %d ended\n",z);
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

        //First save our 'Header' of length and width
        //printf("length = %d, width = %d", length, width);
        SAVE.write((char*)&width, sizeof(int));
        SAVE.write((char*)&length, sizeof(int));

        //Then save the rest of the data
        for (i = 0; i < width; i++)
        {
            for (j = 0; j < length; j++)
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
}

void TerrainGenerator::LoadHeightMap(int xpos, int zpos, int oldx, int oldz, int frstrn)
{
    ifstream LOAD ("map1.bin", ios::in | ios::binary);
    if (LOAD.is_open())
    {
        int i, j, x, z;
        int startx, startz, endx, endz;
        float check;
        int pos;

        //printf("xpos = %d\nzpos = %d\n", xpos, zpos);
        if ( frstrn == 1)
        {
            //Load Length and Width;
            LOAD.seekg(0, ios::beg);
            LOAD.read((char*)&width, sizeof(int));
            LOAD.read((char*)&length, sizeof(int));
            //printf("width = %d, length = %d\n", width, length);

            //Set StartX to the start of the co-ordinates we'll load into memory for now, and endX to the end. Same for Z
            startx = (xpos - 254) + (width / 2);
            if (startx < 0)
            {
                startx = 0;
            }
            endx = (xpos + 255) + (width / 2);
            if (endx > width)
            {
                endx = width;
            }
            startz = ((zpos - 255) * -1) + (length / 2);
            if (startz < 0)
            {
                startz = 0;
            }
            endz = ((zpos + 254) * -1) + (length / 2);
            if (endz > length)
            {
                endz = length;
            }
            //printf("StartX = %d, EndX = %d\nStartZ = %d, EndZ = %d\n", startx, endx, startz, endz);

            //Load X and Z positions into active heightmap
            x = 0;
            for (i = startx; i <= endx; i++)
            {
                z = 0;
                for (j = startz; j >= endz; j--)
                {
                    pos = ((i * sizeof(float) * width) + (j * sizeof(float)) + (2 * sizeof(int)));
                    //printf("pos = %d\n", pos);
                    LOAD.seekg(pos, ios::beg);
                    LOAD.read((char*)&check, sizeof(float));
                    scaledheightmap[x][z] = check;
                    //printf("x = %d\nz = %d\n",x,z);
                    check = 0;
                    z = z+1;
                }
                x = x+1;
            }
            scaled = 1;
        }
        else if (frstrn == 0)
        {
            LOAD.seekg(0, ios::beg);
            LOAD.read((char*)&width, sizeof(int));
            LOAD.read((char*)&length, sizeof(int));

            //Create necessary extra variables
            int xdifference, zdifference;

            //Re-arrange shit
            xdifference = xpos - oldx;
            zdifference = zpos - oldz;

            if (xdifference > 0)
            {
                for (j = 0; j < 512; j++)
                {
                    for (i = xdifference; i < 512; i++)
                    {
                        scaledheightmap[i - xdifference][j] = scaledheightmap[i][j];
                    }
                }
            }
            else if (xdifference < 0)
            {
                for (j = 0; j < 512; j++)
                {
                    for (i = 511; i > (-1 * xdifference); i--)
                    {
                        scaledheightmap[i][j] = scaledheightmap[i+xdifference][j];
                    }
                }
            }

            if (zdifference > 0)
            {
                for (i = 0; i < 512; i++)
                {
                    for (j = zdifference; j < 512; j++)
                    {
                        scaledheightmap[i][j-zdifference] = scaledheightmap[i][j];
                    }
                }
            }
            else if (zdifference < 0)
            {
             for (i = 0; i < 512; i++)
                {
                    for (j = 511; j > (-1 * zdifference); j--)
                    {
                        scaledheightmap[i][j] = scaledheightmap[i][j+zdifference];
                    }
                }
            }

            //Debug
            //printf("xdifference = %d\nzdifference = %d\n",xdifference,zdifference);

            //Load Shit
            /** THIS HAS SOME FUNKY ASS MATH THAT EVEN I ONLY KIND OF GET, AND I CAME UP WITH IT.
            DO NOT TOUCH **/
            //Load width
            z = 0;
            for (j = 0; j < 512; j++)
            {
                if (xdifference > 0)
                {
                    /**Set start and end x and z. In this case, startx is the array-modified xpos, endx is where to start
                    loading new values from in terms of the array**/
                    //printf("xpos = %d, zpos = %d\n", xpos, zpos);
                    startx = xpos + (width / 2);
                    startz = ((zpos + 255 ) * -1) + (length / 2);
                    //printf("startx = %d, startz = %d, ",startx,startz);
                    endx = 255 - xdifference;
                    //printf("endx = %d\n",endx);
                    int toolong = 0;
                    if ((startx + endx + xdifference) > width)
                    {
                        toolong = (startx + endx + xdifference) - width;
                        for (i = (512 - toolong); i < 512; i++)
                        {
                            scaledheightmap[i][j] = 0;
                        }
                        printf("xtoolong = %d\n",toolong);
                    }

                    if ((startx + endx) > width)
                    {
                        for (i = (512 - xdifference); i < 512; i++)
                        {
                            scaledheightmap[i][j] = 0;
                        }
                    }
                    else
                    {
                        x = 0;
                        for (i = (511 - xdifference); i < (512 - toolong); i++)
                        {
                            pos = ((2 * sizeof(int)) + ((startx + (endx) + x) * sizeof(float) * width) + ((startz + z) * sizeof(float)));
                            //printf("pos = %d\n", pos);
                            LOAD.seekg(pos, ios::beg);
                            LOAD.read((char*)&check, sizeof(float));
                            scaledheightmap[i][j] = check;
                            //printf("x = %d\nz = %d\n",x,z);
                            check = 0;
                            x = x + 1;
                        }
                    }
                }
                else if (xdifference < 0)
                {
                   /**Set start and end x and z. In this case, startx is the array-modified xpos, endx is where to start
                    loading new values from in terms of the array**/
                    startx = xpos + (width / 2);
                    startz = ((zpos + 255 ) * -1) + (length / 2);
                    endx = 255 + xdifference;
                    int tooshort = 0;
                    if ((startx - endx + xdifference) < 0)
                    {
                        tooshort = ((startx - endx + xdifference) * -1);
                        for (i = 0; i < tooshort; i++)
                        {
                            scaledheightmap[i][j] = 0;
                        }
                        printf("xTooshort = %d",tooshort);
                    }

                    if ((startx - endx) < 0)
                    {
                        for (i = 0; i < (-1 * xdifference); i++)
                        {
                            scaledheightmap[i][j] = 0;
                        }
                    }
                    else
                    {
                        x = 0;
                        for (i = (-1 * xdifference); i >= 0 + tooshort; i--)
                        {
                            pos = ((2 * sizeof(int)) + ((startx - endx - x) * sizeof(float) * width) + ((startz + z) * sizeof(float)));
                            //printf("pos = %d\n", pos);
                            LOAD.seekg(pos, ios::beg);
                            LOAD.read((char*)&check, sizeof(float));
                            scaledheightmap[i][j] = check;
                            //printf("x = %d\nz = %d\n",x,z);
                            check = 0;
                            x = x + 1;
                        }
                    }
                }
            z = z + 1;
            }

            //Attempt to load fewer points, thereby using less HDD and optimising performance
            int startinc = 0;
            int enddec = 0;
            if (xdifference > 0)
            {
                enddec = xdifference;
                startinc = 0;
            }
            else if (xdifference < 0)
            {
                startinc = (-1 * xdifference);
                enddec = 0;
            }

            //Loading length
            x = 0;
            for (i = 0 + startinc; i < 512 - enddec; i++)
            {
                if (zdifference > 0)
                {
                    /**Set start and end x and z. In this case, startx is the array-modified xpos, endx is where to start
                    loading new values from in terms of the array**/
                    startx = (xpos - 255) + (width / 2);
                    startz = (zpos * -1) + (length / 2);
                    endz = 255 - zdifference;
                    //printf("For zdif > 0\nxpos = %d, zpos = %d\n startx = %d, startz = %d, endz = %d, length = %d\n",xpos,zpos,startx,startz,endz,length);
                    int toolong = 0;
                    if ((startz + endz + zdifference) > length)
                    {
                        toolong = (startz + endz + zdifference) - length;
                        for (j = (511 - toolong); j < 512; j++)
                        {
                            scaledheightmap[i][j] = 0;
                        }
                        printf("ztoolong = %d\n",toolong);
                    }

                    if ((startz + endz) > length)
                    {
                        for (j = (511 - zdifference); j < 512; j++)
                        {
                            scaledheightmap[i][j] = 0;
                        }
                    }
                    else
                    {
                        z = 0;
                        for (j = (511 - zdifference); j < (512 - toolong); j++)
                        {
                            pos = ((2 * sizeof(int)) + ((startx + x) * sizeof(float) * width) + ((startz + endz + z) * sizeof(float)));
                            //printf("pos = %d\n", pos);
                            LOAD.seekg(pos, ios::beg);
                            LOAD.read((char*)&check, sizeof(float));
                            scaledheightmap[i][j] = check;
                            //printf("x = %d\nz = %d\n",x,z);
                            check = 0;
                            z = z + 1;
                        }
                    }
                }
                else if (zdifference < 0)
                {
                   /**Set start and end x and z. In this case, startx is the array-modified xpos, endx is where to start
                    loading new values from in terms of the array**/
                    startx = (xpos - 255) + (width / 2);
                    startz = (zpos * -1) + (length / 2);
                    endx = 255 + zdifference;
                    //printf("For zdif < 0\nxpos = %d, zpos = %d\n startx = %d, startz = %d, endz = %d, length = %d\n",xpos,zpos,startx,startz,endz,length);
                    int tooshort = 0;
                    if ((startz - endz + zdifference) < 0)
                    {
                        tooshort = ((startz - endz + zdifference) * -1);
                        for (i = 0; j < tooshort; j++)
                        {
                            scaledheightmap[i][j] = 0;
                        }
                        printf("zTooshort = %d",tooshort);
                    }

                    if ((startz - endz) < 0)
                    {
                        for (j = 0; j < (-1 * zdifference); j++)
                        {
                            scaledheightmap[i][j] = 0;
                        }
                    }
                    else
                    {
                        z = 0;
                        for (j = (-1 * zdifference); j >= 0 + tooshort; j--)
                        {
                            pos = ((2 * sizeof(int)) + ((startx + x) * sizeof(float) * width) + ((startz - endz - z) * sizeof(float)));
                            //printf("pos = %d\n", pos);
                            LOAD.seekg(pos, ios::beg);
                            LOAD.read((char*)&check, sizeof(float));
                            scaledheightmap[i][j] = check;
                            //printf("x = %d\nz = %d\n",x,z);
                            check = 0;
                            z = z + 1;
                        }
                    }
                }
                x = x + 1;
            }
        }
    }
    else
    {
        printf("Error Re-Openning File\n");
    }
}

/**
    We're doing some funky ass counting, so length array [2nd dimension] values are (z * -1) + (length / 2),
    while the first dimension [x values] are (x + (width / 2))
**/
int TerrainGenerator::GetHeightAtPoint(int x, int z)
{
    if (scaled == 0)
    {
        return heightmap[x + (width / 2)][(z * -1) + (length / 2)];
    }
    else if (scaled == 1)
    {
        return scaledheightmap[256+x][256+z];
    }
    return -1;
}
