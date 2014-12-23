#include <SDL.h>
#include <stdio.h>
#include <string.h>

#include "src\render\GameWindow.h"
#include "src\game\Global.h"

#define SCREEN_HEIGHT   1280
#define SCREEN_WIDTH    720

bool running = true;

GameWindow window;
SDL_Event event;

//Basic window input handing
void g_handleInput()
{
    while(SDL_PollEvent(&event) != 0)
    {
        switch(event.type)
        {
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                running = false;
                break;
            }

            if(event.key.keysym.sym == SDLK_RCTRL) //Check for a right alt press
            {
                if(event.key.keysym.sym == SDLK_RETURN)
                {
                    //Cheap set fullscreen function
                    if(window.r_isFullscreen() == false)
                    {
                        SDL_SetWindowFullscreen(window.r_getGameWindow(), SDL_WINDOW_FULLSCREEN);
                    }
                }
            }
        }
    }
}

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

    //Debug variables
    //int FUCKYOU;

    while(window.r_isRunning())
    {
        g_handleInput();

        //GameState logic
        //Only Draw if FPS
        Currenttime = SDL_GetTicks();

        if ((Currenttime - Lasttime) >= 1000/FPS)
        {
            g_currentState->update();
            g_currentState->render();
            Lasttime = SDL_GetTicks();

            SDL_Delay((Currenttime - Lasttime) / 1000);
        }
            window.r_refresh();
    }
        return 0;
}
