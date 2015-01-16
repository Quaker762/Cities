#include <SDL.h>
#include <stdio.h>
#include <string.h>

#include "src\render\GameWindow.h"
#include "src\game\Global.h"
#include "include\Terrain Generator.h"

#define SCREEN_HEIGHT   1280
#define SCREEN_WIDTH    720

bool running = true;

GameWindow window;
SDL_Event event;
TerrainGenerator WORLDSPACE;

int main(int argc, char* argv[])
{
    /**
        Basic game loop style shit, yo
    **/

    window.r_init();

    g_currentState->init();

    //Declare FPS variables
    int FPS = 120;
    int32_t Currenttime;
    int32_t Lasttime = 0;

    //Declare Terrain Variables
    GLuint terrainDL;
    float xOffset;
    float yOffset;
    float zOffset;


    //Temporary Create Worldspace -> Will need title space and then move to hear when getting to game state
    string File = "map.tga";
    xOffset = 0;
    yOffset = -150;
    zOffset = 0;
    WORLDSPACE.BuildHeightMap(File);
    /**WORLDSPACE.ScaleHeightMap(); **/ //Need to fix scaling, random shit happening ATM
    terrainDL = WORLDSPACE.UpdateHeightMap(xOffset, yOffset, zOffset);


    //Debug variables
    //int FUCKYOU;

    while(window.r_isRunning())
    {

        //GameState logic
        //Only Draw if FPS
        Currenttime = SDL_GetTicks();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        if ((Currenttime - Lasttime) >= 1000/FPS)
        {
            g_currentState->handleInput(window);
            g_currentState->update();
            g_currentState->render();
            glCallList(terrainDL);
            Lasttime = SDL_GetTicks();
            window.r_refresh();
        }
    }
        return 0;
}
