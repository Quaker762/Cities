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
    g_currentState->init();
    g_currentState->render();
    window->r_SplashRefresh();

    //Declare FPS variables
    int FPS = 60;
    int Currenttime;
    int Lasttime = 0;

    //Wait, then swap to in-game state and init
    /**
        if(Running Windows) //HOW do we do this nicely? I can think of some shit ways to do it, hopefully an easy way.
    **/
    Sleep(1000);
    g_currentState->destroy();
    SDL_RenderClear(window->r_renderer);
    g_changeState(CGAMESTATE);
    g_currentState->init();

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
