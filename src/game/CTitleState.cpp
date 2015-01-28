#include <cmath>

#include "..\include\CGameState.h"
#include "..\include\Camera.h"
#include "..\include\Global.h"
#include "..\include\GameWindow.h"

SDL_Surface* windowsurf = NULL;
SDL_Surface* logo = NULL;
SDL_Texture* tex = NULL;
SDL_Rect     c_rect; //The rectangle to clear our screen

//Audio stuff
Mix_Chunk* fx = NULL;

int alpha = 0;

CTitleState::CTitleState()
{

}

CTitleState::~CTitleState()
{

}

void CTitleState::init()
{
    logo = SDL_LoadBMP("data/image/logo.bmp");
    tex = SDL_CreateTextureFromSurface(window->r_renderer, logo);
    SDL_SetRenderDrawBlendMode(window->r_renderer, SDL_BLENDMODE_BLEND);

    c_rect.w = window->getWidth();
    c_rect.h = window->getHeight();
    c_rect.x = 0;
    c_rect.y = 0;

    //Audio init
    fx = Mix_LoadWAV("data/audio/misc/splsfx2.wav");

    Mix_PlayChannel(-1, fx, 0); //Play our Audio
}

void CTitleState::destroy()
{
    SDL_FreeSurface(logo);
    logo = NULL;
    tex = NULL;
    Mix_FreeChunk(fx);
}

void CTitleState::handleInput()
{

}

void CTitleState::update()
{
    SDL_PollEvent(&event);

    alpha = 255 - SDL_GetTicks() / 40;

    if(alpha <= 0)
        alpha = 0 + SDL_GetTicks() / 40;

    if(SDL_GetTicks() >= 3000) //This is about 3 seconds long.
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
    SDL_SetRenderDrawColor(window->r_renderer, 255, 255, 255, alpha);
    SDL_RenderCopy(window->r_renderer, tex, NULL, &c_rect);
    SDL_RenderFillRect(window->r_renderer, &c_rect); //Alpha rectangle
    SDL_RenderPresent(window->r_renderer);
}
