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
    Camera(GLfloat x, GLfloat y, GLfloat z);
    ~Camera();

    void update(glm::vec3 posvec);

    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();

private:

    glm::vec3 pos;
    GLfloat angle;
};



#endif // CAMERA_H
