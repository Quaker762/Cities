#include <cmath>

#include "CGameState.h"
#include "Camera.h"
#include "../include/Terrain Generator.h"

float time = 0.0f;

Camera gamecam(0.0f, 0.0f, -3.0f);
TerrainGenerator WORLDSPACE;

GLuint terrainDL;

int lastxrel = 0;
int lastyrel = 0;

CInGameState::CInGameState()
{

}

CInGameState::~CInGameState()
{

}

void CInGameState::init()
{
    initLighting();
    //Temporary Create Worldspace -> Will need title space and then move to hear when getting to game state
    std::string File = "map.tga";
    xOffset = 0;
    yOffset = -400;
    zOffset = 0;
    WORLDSPACE.BuildHeightMap(File);
    //WORLDSPACE.GenerateHeightMap();
    WORLDSPACE.ScaleHeightMap();
    WORLDSPACE.SmoothHeightMap(1);
    terrainDL = WORLDSPACE.UpdateHeightMap(xOffset, yOffset, zOffset);
}

void CInGameState::destroy()
{

}

void CInGameState::handleInput(GameWindow& window)
{
    int height = WORLDSPACE.GetHeightAtPoint(gamecam.getX(), gamecam.getZ());

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

            if(event.key.keysym.sym == SDLK_SPACE)
            {
                gamecam.updatePos(0.0f, 1.5f, 0.0f, 0.0f);
            }

            if(event.key.keysym.sym == SDLK_LCTRL)
            {
                gamecam.updatePos(0.0f, -1.5f, 0.0f, 0.0f);
            }
        }

        if(event.type == SDL_MOUSEWHEEL)
        {
            gamecam.updatePos(0.0f, (GLfloat)event.wheel.y, 0.0f, 0.0f);
        }

        if(event.type == SDL_MOUSEMOTION)
        {
            gamecam.rotate(event.motion.xrel, event.motion.yrel);
            /**
                This sort of works. How it really should work is:
                1. The current world X and Z co-ordinates are actually our origin for selection
                2. We should count how many pixels the mouse has moved IN RELATION to the current X and Z co-ords
            **/
            //std::cout << "Height: " << WORLDSPACE.GetHeightAtPoint(gamecam.getX() + event.motion.xrel , gamecam.getY() + event.motion.yrel) << std::endl;
        }
    }
}

void CInGameState::update()
{
    if(gamecam.getY() > (WORLDSPACE.GetHeightAtPoint(gamecam.getX(), gamecam.getZ()) + 55 + yOffset) | gamecam.getY() < (WORLDSPACE.GetHeightAtPoint(gamecam.getX(), gamecam.getZ()) + 45 + yOffset))
    {
        gamecam.updatePos(0.0f, ((WORLDSPACE.GetHeightAtPoint(gamecam.getX(), gamecam.getZ()) + 50 +yOffset) - gamecam.getY() ) * 0.5f, 0.0f, 0.0f);
    }
    gamecam.look();
}

void CInGameState::render()
{
    glCallList(terrainDL);

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

void CInGameState::initLighting()
{
    glEnable(GL_LIGHT1);

    //glLightfv(GL_LIGHT0, GL_AMBIENT, 0);
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
