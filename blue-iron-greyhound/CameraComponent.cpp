#include "CameraComponent.h"
#include "GameObject.h"

#define DEG_TO_RADIAN 0.017453293

Camera::Camera(glm::vec3 eye, glm::vec3 at, glm::vec3 up, float r)
{
	this->eye = eye;
	this->at = at;
	this->up = up;
	this->rotation = r;
}


void Camera::init()
{
	offset = glm::vec3(0.0, 2.0, 10.0);
}


void Camera::update()
{
	this->eye = getUser()->getTranslation();
	this->eye += offset;
	
	this->rotation = getUser()->getCameraRotation();

	this->at = glm::vec3(eye.x + 1.0f*std::sin(rotation*DEG_TO_RADIAN), eye.y, eye.z - 1.0f*std::cos(rotation*DEG_TO_RADIAN));

}



glm::vec3 Camera::getEye()
{
	return eye;
}

glm::vec3 Camera::getAt()
{
	return at;
}
glm::vec3 Camera::getUp()
{
	return up;
}
float Camera::getRotation()
{
	return rotation;
}