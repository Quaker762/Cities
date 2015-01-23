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

void CTitleState::render()
{
    SDL_BlitSurface(logo, NULL, windowsurf, NULL);
    SDL_RenderPresent(window->r_renderer);
}
