#include "Camera.h"
#define PI 3.1415926535897932384626433

Camera::Camera(GLfloat x, GLfloat y, GLfloat z)
{
    //Initialise the camera
    _pos = glm::vec3(x, y, z);
}

Camera::~Camera()
{

}

void Camera::updatePos(GLfloat x, GLfloat y, GLfloat z, GLfloat LRTrue)
{
    if (LRTrue == 1)
    {
        _pos = glm::vec3(_pos.x + (x * sin( getYaw() ) ), _pos.y + y, _pos.z + (z * cos( getYaw() ) ));
    }
    else if (LRTrue == 0)
    {
        _pos = glm::vec3(_pos.x + (x * cos( getYaw() ) ), _pos.y + y, _pos.z + (z * sin( getYaw() ) ));
    }

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

    _pitchang = _pitchang + (0.005 * npitch);
    _yawang = _yawang + (0.01 * nyaw);
}


void Camera::look()
{
    gluLookAt(getX(), getY(), getZ(), getX() + cos(getYaw()), getY() + 5*sin(getPitch()+0.5*PI), getZ() + sin(getYaw()), 0.0, 1.0, 0.0);
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

