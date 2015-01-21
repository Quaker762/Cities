#include <cmath>

#include "CGameState.h"
#include "Camera.h"
#include "Global.h"

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
}

void CTitleState::render()
{
    SDL_RenderCopy(window->r_renderer, tex, NULL, NULL); //TODO: Alpha to fade image in??? Need .png??
}
