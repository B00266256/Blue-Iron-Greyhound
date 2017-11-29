#include "MovementComponent.h"
#include <iostream>

MovementComponent::MovementComponent(std::string name)
{
}

MovementComponent::~MovementComponent()
{
}

void MovementComponent::init()
{
	moveVector = glm::vec3(0.0f, 0.0f, 0.0f);
}

void MovementComponent::update()
{
	//Reset the movement vector...
	moveVector = glm::vec3(0.0f, 0.0f, 0.0f);
	//Check for input...
	if (this->input->keyPressed("W"))
		moveForward();
	if (this->input->keyPressed("S"))
		moveBackwards();
	if (this->input->keyPressed("A"))
		moveLeft();
	if (this->input->keyPressed("D"))
		moveRight();
	//Update the user's position by the movement vector...
	//std::cout << moveVector.x << " ::: " << moveVector.y << " ::: " << moveVector.z << std::endl; //DEBUG LINE
	//std::cout << this->user->getPosition().x << "/" << this->user->getPosition().y << "/" << this->user->getPosition().z << std::endl; //DEBUG LINE
	this->user->setPosition(this->user->getPosition() + moveVector);
}

void MovementComponent::moveForward() { moveForward(0.5f); }
void MovementComponent::moveBackwards() { moveBackwards(0.5f); }
void MovementComponent::moveRight() { moveRight(0.5f); }
void MovementComponent::moveLeft() { moveLeft(0.5f); }

void MovementComponent::moveForward(float distance)
{
	moveVector += glm::vec3(0.0f + distance*std::sin(this->user->getRotation()*DEG_TO_RADIAN), 0.0f, 0.0f - (distance)*std::cos(this->user->getRotation()*DEG_TO_RADIAN));
}

void MovementComponent::moveBackwards(float distance)
{
	moveVector -= glm::vec3(0.0f + distance*std::sin(this->user->getRotation()*DEG_TO_RADIAN), 0.0f, 0.0f - distance*std::cos(this->user->getRotation()*DEG_TO_RADIAN));
}

void MovementComponent::moveRight(float distance)
{
	moveVector += glm::vec3(0.0f + distance*std::cos(this->user->getRotation()*DEG_TO_RADIAN), 0.0f, 0.0f + distance*std::sin(this->user->getRotation()*DEG_TO_RADIAN));
}

void MovementComponent::moveLeft(float distance)
{
	moveVector -= glm::vec3(0.0f + distance*std::cos(this->user->getRotation()*DEG_TO_RADIAN), 0.0f, 0.0f + distance*std::sin(this->user->getRotation()*DEG_TO_RADIAN));
}

void MovementComponent::setInput(InputSystem * newInput)
{
	this->input = newInput;
}
