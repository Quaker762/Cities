#include "Camera.h"

Camera::Camera(GLfloat x, GLfloat y, GLfloat z)
{
    //Initialise the camera
    _pos = glm::vec3(x, y, z);
}

Camera::~Camera()
{

}

void Camera::updatePos(GLfloat x, GLfloat y, GLfloat z)
{
    _pos = glm::vec3(_pos.x + x, _pos.y + y, _pos.z + z);

}

void Camera::rotate(GLdouble nyaw, GLdouble npitch)
{
    //THIS IS VERY ROUGH!!!!
    if(_pitchang >= PITCH_LOCK)
    {
        _pitchang = PITCH_LOCK; //Ewww, nasty hack here...
    }

    if(_pitchang <= 0)
    {
        _pitchang = 0;
    }

    _pitchang += npitch;
    _yawang += nyaw;
}

//Update where our camera is looking (by moving the world hehehehe)
void Camera::look()
{
    //Oookaay, this is sort of weird, but it works for now...
    //We should probably fix this up, because changing the location of the world
    //can result in some bizzare things.
    //glTranslatef(getX(), getY(), getZ());
    //glRotatef(getYaw(), 0.0f, 1.0f, 0.0f);
    //glRotatef(getPitch(), 1.0f, 0.0f, 0.0f);
    gluLookAt((GLdouble)getX() + sin(getPitch), (GLdouble)getY() + - cos(getYaw()), (Gldouble)getZ(), (Gldouble)getX(), (Gldouble)getY(), (GLdouble)getZ(), 0.0, 1.0, 0.0);
}

GLfloat Camera::getX()
{
    return _pos.x;
}

GLfloat Camera::getY()
{
    return _pos.y;
}

GLfloat Camera::getZ()
{
    return _pos.z;
}

GLdouble Camera::getYaw()
{
    return _yawang;
}

GLdouble Camera::getPitch()
{
    return _pitchang;
}

