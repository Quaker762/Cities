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

void CTitleState::render()
{
   // SDL_FillRect(window.r_getDrawSurface(), NULL, SDL_MapRGB(window.r_getDrawSurface()->format, 0xFF, 0xFF, 0x00));
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}


