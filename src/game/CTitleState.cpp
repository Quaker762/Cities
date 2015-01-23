#include <cmath>

#include "CGameState.h"
#include "Camera.h"
#include "Global.h"
#include "../render/GameWindow.h"

SDL_Surface* windowsurf = NULL;
SDL_Surface* logo = NULL;
SDL_Texture* tex = NULL;

CTitleState::CTitleState()
{

}

CTitleState::~CTitleState()
{

}

void CTitleState::init()
{
    windowsurf = SDL_GetWindowSurface(window->r_getGameWindow());
    logo = SDL_LoadBMP("data/image/logo.bmp");
    tex = SDL_CreateTextureFromSurface(window->r_renderer, logo);
}

void CTitleState::destroy()
{
    SDL_FreeSurface(logo);
    logo = NULL;
    tex = NULL;
}

void CTitleState::handleInput()
{

}

void CTitleState::update()
{
    SDL_PollEvent(&event);

    if(SDL_GetTicks() >= 4000)
        g_changeState(CGAMESTATE);
}

/* The renderer works pretty much like a big canvas:
  when you RenderCopy you are adding paint, each time adding it
  on top.
  You can change how it blends with the stuff that
  the new data goes over.
  When your 'picture' is complete, you show it
  by using SDL_RenderPresent. */

  /* SDL 1.2 hint: If you're stuck on the whole renderer idea coming
  from 1.2 surfaces and blitting, think of the renderer as your
  main surface, and SDL_RenderCopy as the blit function to that main
  surface, with SDL_RenderPresent as the old SDL_Flip function.*/

void CTitleState::render()
{
    //SDL_BlitSurface(logo, NULL, windowsurf, NULL);
    SDL_RenderCopy(window->r_renderer, tex, NULL, NULL);
    SDL_RenderPresent(window->r_renderer);
}
