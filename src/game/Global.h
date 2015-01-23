#ifndef GLOBAL_H
#define GLOBAL_H

#include <string>
#include <iostream>
#include <stdlib.h>
#include <GL\glu.h>
#include <SDL_opengl.h>
#include <SDL_mixer.h>

#ifdef _WIN32
    #include <windows.h>
#endif

#ifdef __APPLE__
    #include <MACOS.h> //TODO: Find where the goddamn OSX header file is...
#endif

#include <SDL.h>

#include "CGameState.h"

enum gameStates
{
    CSPLASHSTATE,
    CTITLESTATE,
    CMENUSTATE,
    CGAMESTATE,
    CCREDITSTATE,
    CGLTESTSTATE,
    CNULLSTATE
};

//Current gamestate
extern CGameState* g_currentState;
extern GameWindow* window;

//External function definitions
extern void g_changeState(uint8_t stateID);
extern void die(std::string message);
extern void g_cleanup();

//External Audio functions
extern void a_initAudio();

#endif // GLOBAL_H
