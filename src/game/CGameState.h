#ifndef CGAMESTATE_H
#define CGAMESTATE_H

#include <SDL.h>
#include <GL\glu.h>
#include <SDL_opengl.h>
#include <string>
#include <iostream>

#include "../render/GameWindow.h"

#define NULLSTATE -1
#define SPLASH 0
#define MENU 1
#define GAME 2

class CGameState
{
public:
    CGameState() {};
    virtual ~CGameState() {};
    virtual void init() = 0; //Do we need these if we have a constructor and destructor???
    virtual void destroy() = 0;
    virtual void handleInput(GameWindow& window) = 0;
    virtual void update() = 0;
    virtual void render() = 0;

private:
};

class CTitleState : public CGameState
{
public:
    CTitleState();
    ~CTitleState();
    void init();
    void destroy();
    void handleInput(GameWindow& window);
    void update();
    void render();

private:
    SDL_Event event;
};

class CInGameState : public CGameState
{
    public:
    CInGameState();
    ~CInGameState();
    void init();
    void destroy();
    void handleInput(GameWindow& window);
    void update();
    void render();

    void initLighting();

private:
    SDL_Event event;
    //Declare Terrain Variables
    float xOffset;
    float yOffset;
    float zOffset;
};

#endif // CGAMESTATE_H
