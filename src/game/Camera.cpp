#include "Camera.h"

Camera::Camera(GLfloat x, GLfloat y, GLfloat z)
{
    //Initialise the camera
    pos = glm::vec3(x, y, z);
}

Camera::~Camera()
{

}

void Camera::update(glm::vec3 posvec)
{
    //TODO: Mouse input here, change vec3 accordingly.
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

