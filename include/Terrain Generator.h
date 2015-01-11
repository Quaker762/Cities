#ifndef TERRAINGENERATOR_H
#define TERRAINGENERATOR_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <GL\glu.h>
#include <cmath>
#include <string>
#include <math.h>

using namespace std;


class TerrainGenerator
{
    public:
        TerrainGenerator();
        virtual ~TerrainGenerator();
        void BuildHeightMap(string File);
        void ScaleHeightMap();
        int EditHeightMap();
        int UpdateHeightMap();
        int SaveHeightMap();
    protected:
    private:
        unsigned char heightmap[1000][1000];
        int scaledheightmap[1000][1000];
        short int width;
        short int length;
};

#endif // TERRAIN GENERATOR_H