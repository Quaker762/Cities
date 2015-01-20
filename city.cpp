#include <SDL.h>
#include <stdio.h>
#include <string.h>

#include "src\render\GameWindow.h"
#include "src\game\Global.h"

int main(int argc, char* argv[])
{
    /**
        Basic game loop style shit, yo
    **/

    g_changeState(CTITLESTATE);
    window->r_init();

    g_currentState->init();

    //Declare FPS variables
    int FPS = 60;
    int Currenttime;
    int Lasttime = 0;

    while(window->r_isRunning())
    {
        Currenttime = SDL_GetTicks();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        if ((Currenttime - Lasttime) >= 1000/FPS)
        {
            g_currentState->handleInput();
            g_currentState->update();
            g_currentState->render();
            Lasttime = SDL_GetTicks();
        }
        window->r_refresh();
    }
    g_cleanup();
    return 0;
}
