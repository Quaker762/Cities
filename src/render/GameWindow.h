#ifndef GAMEWINDOW_H_
#define GAMEWINDOW_H_

#include <SDL.h>
#include <stdio.h>

#define DEFAULT_WIDTH   640
#define DEFAULT_HEIGHT  480

class GameWindow
{
private:
    int16_t width,  height;
    SDL_Window*     r_window;
    SDL_Surface*    r_surface;

public:
    GameWindow();
    ~GameWindow();
    void r_init();
    void r_redraw();
    void r_setWindowSize(int16_t width, int16_t height);

};

#endif // GAMEWINDOW_H_
