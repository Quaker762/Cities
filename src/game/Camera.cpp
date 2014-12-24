#include "Camera.h"

Camera::Camera()
{
    //Initialise the camera
    pos = glm::vec3(0.0f, 0.0f, -6.0f);
}

Camera::~Camera()
{

}

void Camera::update(glm::vec3 posvec)
{
    //TODO: Mouse input here, change vec3 accordingly.
}
