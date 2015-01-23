#include "Global.h"

CGameState* g_currentState = new CTitleState();
GameWindow* window = new GameWindow();

void g_changeState(uint8_t stateID)
{
    g_currentState->destroy();
    delete g_currentState; //Free up memory the current state was using
    g_currentState = NULL;

    switch(stateID)
    {
        case CNULLSTATE:
            g_currentState = nullptr;
            break;
        case CTITLESTATE:
            g_currentState = new CTitleState();
            break;
        case CGAMESTATE:
            g_currentState = new CInGameState();
            break;
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

void g_cleanup()
{
    delete window;
    delete g_currentState;
}

//AUDIO STUFF
void a_initAudio()
{
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
    {
        die("Unable to intialise Audio correctly!");
    }
}
