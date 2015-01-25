#include "..\include\GameWindow.h"

#include "..\include\Global.h"

//Class constructor
GameWindow::GameWindow(int nwidth, int nheight)
{
    width = nwidth;
    height = nheight;
}

//Class destructor
GameWindow::~GameWindow()
{
    SDL_DestroyWindow(r_window);
    SDL_GL_DeleteContext(r_glContext);
    SDL_Quit(); //Kill Engine
}

void GameWindow::r_init()
{
    SDL_DestroyWindow(r_window);
    SDL_GL_DeleteContext(r_glContext);

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
    SDL_SetRelativeMouseMode(SDL_TRUE); //Trap the mouse inside our screen

    r_window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);
    r_glContext = SDL_GL_CreateContext(r_window);
    r_renderer = SDL_CreateRenderer(r_window, -1, SDL_RENDERER_SOFTWARE);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(75.0f, (GLfloat)getWidth()/(GLfloat)getHeight(), 0.01f, 2000.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glEnable(GL_BLEND);                                 //Enable blending
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);          // Draw everything as a wireframe

	//glEnable(GL_LIGHTING); //Enable lighting!
	glEnable(GL_COLOR_MATERIAL); //Make Color3f work (for the moment)
}

void GameWindow::r_shutdown()
{
    running = false;
    SDL_DestroyWindow(r_window);
    SDL_DestroyRenderer(r_renderer);
    SDL_GL_DeleteContext(r_glContext);
    SDL_Quit(); //Kill Engine
}

//Redraw the screen
void GameWindow::r_refresh()
{
    SDL_GL_SwapWindow(r_window);
}

//Temporary redraw splash screen
void GameWindow::r_2Drefresh()
{
    SDL_UpdateWindowSurface(r_window);
}

void GameWindow::r_resize(int nwidth, int nheight)
{
    SDL_SetWindowSize(r_window, nwidth, nheight);
    SDL_GetWindowSize(r_window,&width, &height);

    glViewport(0, 0, width, height); //Make sure our GL stays updated as well

}

int GameWindow::getWidth()
{
    return width;
}

int GameWindow::getHeight()
{
    return height;
}
