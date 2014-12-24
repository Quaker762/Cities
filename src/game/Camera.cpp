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
    //TODO: Mouse input here, change vec3 accordingly.
    pos = glm::vec3(pos.x + x, pos.y + y, pos.z + z);
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

