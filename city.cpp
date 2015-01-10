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
    int FPS = 60;
    int32_t Currenttime;
    int32_t Lasttime = 0;

    //Temporary Create Worldspace -> Will need title space and then move to hear when getting to game state
    string File = "map.tga";
    WORLDSPACE.BuildHeightMap(File);
    WORLDSPACE.ScaleHeightMap();

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
            g_currentState->update();
            g_currentState->handleInput(window);
            g_currentState->render();
            WORLDSPACE.UpdateHeightMap();
            Lasttime = SDL_GetTicks();

            SDL_Delay((Currenttime - Lasttime) / 1000);
        }
            window.r_refresh();
    }
        return 0;
}
