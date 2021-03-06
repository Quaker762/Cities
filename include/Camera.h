#ifndef CAMERA_H
#define CAMERA_H

#include <SDL.h>
#include <SDL_opengl.h>
#include <glm/glm.hpp>
#include <GL\glu.h>
#include <cmath>

//Max Camera angle
#define PITCH_LOCK 90

class Camera
{
public:
    Camera(GLfloat x, GLfloat y, GLfloat z);
    ~Camera();

    void updatePos(GLfloat x, GLfloat y, GLfloat z, GLfloat LRTrue);
    void rotate(GLdouble nyaw, GLdouble npitch);

    void look();

    GLfloat getX();
    GLfloat getY();
    GLfloat getZ();

    GLdouble getYaw();
    GLdouble getPitch();

private:
    glm::vec3 _pos;

    GLdouble _yawang = 0; //Camera yaw angle
    GLdouble _pitchang = 0; //Camera pitch angle
};



#endif // CAMERA_H
