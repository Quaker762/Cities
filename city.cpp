#include <SDL.h>
#include <stdio.h>

#include "src\render\GameWindow.h"

#define SCREEN_HEIGHT   640
#define SCREEN_WIDTH    480

bool running = true;

GameWindow window;

int main(int argc, char* argv[])
{
    /**
        Basic game loop style shit, yo
    **/

    window.r_init();

    SDL_Event event;

    while(running)
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
            }
        }
        window.r_redraw();
    }

    return 0;
}
