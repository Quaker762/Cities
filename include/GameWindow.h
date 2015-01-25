#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <SDL.h>
#include <stdio.h>
#include <SDL_opengl.h>


struct RenderInfo //Render info structure
{
    const GLubyte* vendor;
    const GLubyte* gfxcard;
    const GLubyte* glver;
};

class GameWindow
{
public:
    GameWindow(int nwidth, int nheight);
    ~GameWindow();

    //Class functions
    void            r_init();
    void            r_refresh();
    void            r_2Drefresh();
    void            r_resize(int nwidth, int nheight);
    void            r_shutdown();

    int             getWidth();
    int             getHeight();

    SDL_Window*     r_window;
    SDL_Renderer*   r_renderer;
    SDL_GLContext   r_glContext;

    bool            fullscreen;
    bool            running = true;

private:
    int             width,  height;
    RenderInfo      r_renderInfo;

};

#endif // GAMEWINDOW_H_
