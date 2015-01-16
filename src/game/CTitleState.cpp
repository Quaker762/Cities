#include "CGameState.h"
#include "Camera.h"

float time = 0.0f;

Camera gamecam(0.0f, 0.0f, -3.0f);

CTitleState::CTitleState()
{

}

CTitleState::~CTitleState()
{

}

void CTitleState::init()
{

}

void CTitleState::destroy()
{

}

void CTitleState::handleInput(GameWindow& window)
{
    while(SDL_PollEvent(&event) != 0)
    {
        if(event.type == SDL_QUIT)
        {
            window.r_shutdown();
        }

        if(event.type == SDL_KEYDOWN)
        {
            //Check for escape key press
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                window.r_shutdown();
            }

            if(event.key.keysym.sym == SDLK_LEFT)
            {
                gamecam.updatePos(1.0f * 1.5f, 0.0f, -1.0f * 1.5, 1.0f);
            }

            if(event.key.keysym.sym == SDLK_RIGHT)
            {
                gamecam.updatePos(-1.0f * 1.5f, 0.0f, 1.0f * 1.5, 1.0f);
            }

            if(event.key.keysym.sym == SDLK_UP)
            {
                gamecam.updatePos(1.0f * 1.5f, 0.0f, 1.0f * 1.5, 0.0f);
            }

            if(event.key.keysym.sym == SDLK_DOWN)
            {
                gamecam.updatePos(-1.0f * 1.5f, 0.0f, -1.0f * 1.5, 0.0f);
            }
        }

        if(event.type == SDL_MOUSEWHEEL)
        {
            //gamecam.updatePos(0.0f, 0.0f, (GLfloat)event.wheel.y);
        }

        if(event.type == SDL_MOUSEMOTION)
        {
            gamecam.rotate(event.motion.xrel, event.motion.yrel);
        }
    }

    gamecam.look();
}

void CTitleState::update()
{

}

void CTitleState::render()
{

    //THIS HAS TO BE CALLED BEFORE WE MAKE ANY CHANGES TO MATRIX!!!
    //gluLookAt(0.0, 0.0,(GLdouble)gamecam.getZ(), (GLdouble)gamecam.getX(), (GLdouble)gamecam.getY(), 0.0, 0.0, 1.0, 0.0);

    //Draw a cube
    glBegin(GL_QUADS);
        glColor3f(0.0f,1.0f,0.0f);          // Set The Color To Green
        glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Top)
        glVertex3f(-1.0f, 1.0f, 1.0f);          // Bottom Left Of The Quad (Top)
        glVertex3f( 1.0f, 1.0f, 1.0f);          // Bottom Right Of The Quad (Top)
        glColor3f(1.0f,0.5f,0.0f);          // Set The Color To Orange
        glVertex3f( 1.0f,-1.0f, 1.0f);          // Top Right Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // Top Left Of The Quad (Bottom)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Bottom)
        glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Bottom)
        glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
        glVertex3f( 1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Front)
        glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Front)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Front)
        glVertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Front)
        glColor3f(1.0f,1.0f,0.0f);          // Set The Color To Yellow
        glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Back)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Back)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Back)
        glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Back)
        glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
        glVertex3f(-1.0f, 1.0f, 1.0f);          // Top Right Of The Quad (Left)
        glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f,-1.0f);          // Bottom Left Of The Quad (Left)
        glVertex3f(-1.0f,-1.0f, 1.0f);          // Bottom Right Of The Quad (Left)
        glColor3f(1.0f,0.0f,1.0f);          // Set The Color To Violet
        glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Right)
        glVertex3f( 1.0f, 1.0f, 1.0f);          // Top Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f, 1.0f);          // Bottom Left Of The Quad (Right)
        glVertex3f( 1.0f,-1.0f,-1.0f);          // Bottom Right Of The Quad (Right)
    glEnd();                        // Done Drawing The Quad
}


    //Draw a 2D triangle (in our 3D space)
    /**
    glBegin(GL_TRIANGLES);                  // Begin Drawing Triangles
        glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
        glVertex3f( 0.0f, 1.0f, 0.0f);          // Move Up One Unit From Center (Top Point)
        glColor3f(0.0f,1.0f,0.0f);          // Set The Color To Green
        glVertex3f(-1.0f,-1.0f, 0.0f);          // Left And Down One Unit (Bottom Left)
        glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
        glVertex3f( 1.0f,-1.0f, 0.0f);          // Right And Down One Unit (Bottom Right)
    glEnd();                            // Done Drawing The Quad
    **/
