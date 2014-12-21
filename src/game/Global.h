#ifndef GLOBAL_H
#define GLOBAL_H

#include "CGameState.h"

enum gameStates
{
    CSPLASHSTATE,
    CTITLESTATE,
    CMENUSTATE,
    CGAMESTATE,
    CCREDITSTATE,
    CNULLSTATE
};

//Current gamestate
extern CGameState* g_currentState;

//External functions
extern void g_changeState(uint8_t stateID);

#endif // GLOBAL_H
