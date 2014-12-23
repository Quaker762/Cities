#include "Global.h"

CGameState* g_currentState = new CTitleState();

void g_changeState(uint8_t stateID)
{
    delete g_currentState; //Free up memory the current state was using

    switch(stateID)
    {
<<<<<<< HEAD
        case CNULLSTATE:
            g_currentState = nullptr;
            break;
        case CTITLESTATE:
            g_currentState = new CTitleState();
            break;
=======
    case NULL:
        g_currentState = NULL;
        break;
    case CTITLESTATE:
        g_currentState = new CTitleState();
        break;
>>>>>>> origin/master
    }

    g_currentState->init(); //Call the state's init function
}

//Kill the program if we detect an error
void die(std::string message)
{
    std::string errormsg = "";
    std::string error = SDL_GetError();

    errormsg += message;
    errormsg += "\n";
    errormsg += error;

    //Give a error message box to the user!
    MessageBox(GetActiveWindow(), errormsg.c_str(), "Fatal Error", MB_OK | MB_ICONERROR);

    SDL_Quit();
    exit(EXIT_FAILURE);
}
