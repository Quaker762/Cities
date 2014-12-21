#include "CGameState.h"

CTitleState::CTitleState()
{

}

CTitleState::~CTitleState()
{

}

void CTitleState::init()
{

}

void CTitleState::destroy()
{

}

void CTitleState::update()
{

}

void CTitleState::render(GameWindow& window)
{
    SDL_FillRect(window.r_getDrawSurface(), NULL, SDL_MapRGB(window.r_getDrawSurface()->format, 0xFF, 0x00, 0x00));
}


