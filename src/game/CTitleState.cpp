#include "CGameState.h"

float time = 0;

float x = 0.0f;
float y = 0.0f;
float z = -3.0f;

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

            if(event.key.keysym.sym == SDLK_z)
            {
                z -= 0.5f;
            }
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

    glTranslatef(x, y, z);
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


