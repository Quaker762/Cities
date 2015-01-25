#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <SDL.h>
#include <stdio.h>
#include <SDL_opengl.h>

#define DEFAULT_WIDTH   640
#define DEFAULT_HEIGHT  480

class GameWindow
{
public:
    GameWindow();
    ~GameWindow();

    //Class functions
    void            r_init();
    void            r_refresh();
    void            r_2Drefresh();
    void            r_resize(int nwidth, int nheight);
    void            r_shutdown();

    SDL_Window*     r_window;
    SDL_Renderer*   r_renderer;
    SDL_GLContext   r_glContext;

    bool            fullscreen;
    bool            running = true;

    int             width,  height;

private:

};

#endif // GAMEWINDOW_H_
