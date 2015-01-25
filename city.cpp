#include <SDL.h>
#include <stdio.h>
#include <string.h>
#include "include\GameWindow.h"
#include "include\Global.h"


int main(int argc, char* argv[])
{
    window->r_init();
    a_initAudio(); //Init audio

    g_changeState(CTITLESTATE);

    //Declare FPS variables
    int FPS = 5000;
    long Currenttime = 0;
    long Lasttime = 0;

    while(window->running)
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
            Lasttime = SDL_GetTicks();
        }
    }
    return 0;
}
