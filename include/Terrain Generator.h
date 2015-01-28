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
        void GenerateHeightMap();
        void ScaleHeightMap();
        void SmoothHeightMap(int advancedsmooth);
        int EditHeightMap();
        int UpdateHeightMap(float xOffset, float yOffset, float zOffset, int xpos, int zpos);
        void SaveHeightMap();
        void LoadHeightMap(int xpos, int zpos);
        int GetHeightAtPoint(int x, int z);
    protected:
    private:
        unsigned char heightmap[1000][1000];
        float scaledheightmap[1000][1000];
        short int width;
        short int length;
        unsigned char scaled = 0;
};

#endif // TERRAIN GENERATOR_H
