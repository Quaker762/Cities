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
        if(event.type == SDL_KEYDOWN)
        {
            //Check for escape key press
            if(event.key.keysym.sym == SDLK_ESCAPE)
            {
                window.r_shutdown();
            }
        }

        if(event.type == SDL_MOUSEMOTION)
        {
            gamecam.update(0.0f, 0.0f, (GLfloat)event.motion.yrel * 0.01);
        }
    }
}

void CTitleState::update()
{
    time += 0.1;
}

void CTitleState::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslatef(gamecam.getX(), gamecam.getY(), gamecam.getZ());
    glRotatef(45 * time, 0.0f, 1.0f, 0.0f);

    glBegin(GL_TRIANGLES);                  // Begin Drawing Triangles
        glColor3f(1.0f,0.0f,0.0f);          // Set The Color To Red
        glVertex3f( 0.0f, 1.0f, 0.0f);          // Move Up One Unit From Center (Top Point)
        glColor3f(0.0f,1.0f,0.0f);          // Set The Color To Green
        glVertex3f(-1.0f,-1.0f, 0.0f);          // Left And Down One Unit (Bottom Left)
        glColor3f(0.0f,0.0f,1.0f);          // Set The Color To Blue
        glVertex3f( 1.0f,-1.0f, 0.0f);          // Right And Down One Unit (Bottom Right)
    glEnd();                            // Done Drawing The Quad

}


