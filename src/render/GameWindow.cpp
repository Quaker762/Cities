#include "GameWindow.h"

//Class constructor
GameWindow::GameWindow()
{
    //Set the screen size to a default one.
    width = DEFAULT_WIDTH;
    height = DEFAULT_HEIGHT;
}

//Class destructor
GameWindow::~GameWindow()
{
    SDL_FreeSurface(r_surface);
    r_surface = NULL;

    SDL_DestroyWindow(r_window);
    r_window = NULL;

    SDL_Quit();
}

//Window initialisation routine.
void GameWindow::r_init()
{
    r_window = NULL;
    r_surface = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Initilisation failed with error: %s", SDL_GetError());
        return;
    }
    else
    {
       r_window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
       if(r_window == NULL)
       {
           printf("Window Initilisation failed with error: %s", SDL_GetError());
           return;
       }
       else
       {
           r_surface = SDL_GetWindowSurface(r_window);
           SDL_FillRect(r_surface, NULL, SDL_MapRGB(r_surface->format, 0xFF, 0x00, 0x00));
       }
    }
}

//Redraw the screen
void GameWindow::r_redraw()
{
        SDL_UpdateWindowSurface(r_window);
}


void GameWindow::r_setWindowSize(int16_t width, int16_t height)
{
    SDL_SetWindowSize(r_window, width, height);
}



