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
        int RenderHeightMap(float xOffset, float yOffset, float zOffset, int xpos, int zpos);
        void SmoothHeightMap(int advancedsmooth);
        int EditHeightMap();
        void SaveHeightMap();
        void LoadHeightMap(int xpos, int zpos);
        int GetHeightAtPoint(int x, int z);
    protected:
    private:
        unsigned char heightmap[750][750];
        float scaledheightmap[750][750];
        short int width;
        short int length;
        int framecount = 0;
        unsigned char scaled = 0;
};

#endif // TERRAIN GENERATOR_H
