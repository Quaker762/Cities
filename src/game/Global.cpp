#include "Global.h"
#include "CGameState.h"

CGameState* g_currentState = new CTitleState();

void g_changeState(uint8_t stateID)
{
    delete g_currentState; //Free up memory the current state was using

    switch(stateID)
    {
    case NULL:
        g_currentState = nullptr;
        break;
    case CTITLESTATE:
        g_currentState = new CTitleState();
        break;
    }
}
