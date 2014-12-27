#include "Camera.h"

Camera::Camera(GLfloat x, GLfloat y, GLfloat z)
{
    //Initialise the camera
    pos = glm::vec3(x, y, z);
}

Camera::~Camera()
{

}

void Camera::update(GLfloat x, GLfloat y, GLfloat z)
{
    pos = glm::vec3(pos.x + x, pos.y + y, pos.z + z);
}

void Camera::setAngle(GLdouble nang)
{
    //Check to see if we're not
    if(!angle <= 0 || !angle >= GIMBLE_LOCK)
    {
        //Add the new angle to the current angle
        angle += nang;
    }
}

GLfloat Camera::getX()
{
    return pos.x;
}

GLfloat Camera::getY()
{
    return pos.y;
}

GLfloat Camera::getZ()
{
    return pos.z;
}

