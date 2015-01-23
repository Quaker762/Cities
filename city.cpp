#include <SDL.h>
#include <stdio.h>
#include <string.h>

#include "src\render\GameWindow.h"
#include "src\game\Global.h"

int main(int argc, char* argv[])
{

    //Enter Title State, initialise window and state
    //g_changeState(CTITLESTATE);
    window->r_init();

    g_changeState(CTITLESTATE);

    //Declare FPS variables
    int FPS = 60;
    int Currenttime = 0;
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
            window->r_refresh();
            //window->r_2Drefresh(); //Refresh 2D first
            Lasttime = SDL_GetTicks();
        }
    }
    g_cleanup();
    return 0;
}
