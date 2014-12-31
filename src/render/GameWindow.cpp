#include "GameWindow.h"

#include "../game/Global.h"

//Class constructor
GameWindow::GameWindow()
{
    //Set the screen size to a default one.
    width = 1280;
    height = 720;
}

//Class destructor
GameWindow::~GameWindow()
{
    SDL_DestroyWindow(r_window);
    SDL_GL_DeleteContext(r_glContext);
    SDL_Quit(); //Kill Engine
}

/**
//Window initialisation routine.
void GameWindow::r_init(bool fullscreen)
{
    r_window = NULL;
    r_surface = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL Initilisation failed with error: %s", SDL_GetError());
        return;
    }
    else
    {
       r_window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
       if(r_window == NULL)
       {
           printf("Window Initilisation failed with error: %s", SDL_GetError());
           return;
       }
       else
       {
           r_surface = SDL_GetWindowSurface(r_window);
           SDL_FillRect(r_surface, NULL, SDL_MapRGB(r_surface->format, 0x00, 0x00, 0x00));
       }            window.r_refresh();
    }
}
*/

void GameWindow::r_init()
{
    r_window = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
       die("Failed to initialise variable!!");
    }

    //Intialise OpenGL
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8); /**< Set the size in bits the least amount allocated for each colour */
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); //Enable double buffering

    r_window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    r_glContext = SDL_GL_CreateContext(r_window);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(75.0f, (GLfloat)width/(GLfloat)height, 0.01f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
}

void GameWindow::r_shutdown()
{
    SDL_DestroyWindow(r_window);
    SDL_GL_DeleteContext(r_glContext);
    SDL_Quit(); //Kill Engine
    running = false;
}


//Redraw the screen
void GameWindow::r_refresh()
{
    SDL_GL_SwapWindow(r_window);
}

void GameWindow::r_setWindowSize(int16_t width, int16_t height)
{
    SDL_SetWindowSize(r_window, width, height);
}

bool GameWindow::r_isFullscreen()
{
    return fullscreen;
}

bool GameWindow::r_isRunning()
{
    return running;
}

SDL_Window* GameWindow::r_getGameWindow()
{
    return r_window;
}
