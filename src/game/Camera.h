#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>

//Max Camera angle
#define GIMBLE_LOCK 90

class Camera
{
public:
    Camera();
    ~Camera();

    void update(glm::vec3 posvec);

private:

    glm::vec3 pos;
    GLfloat angle;

    GLint xpos;
    GLint ypos;
    GLint zpos;

};



#endif // CAMERA_H
