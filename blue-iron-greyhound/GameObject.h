/*=============================================================================
* GameObject.h
* Author: Adam Stanton
* Container class for all entities in our game...
=============================================================================*/

#pragma once
#include <vector>
#include <glm\glm.hpp>
#include "Object.h"
#include "Component.h"

class GameObject : public Object
{
public:
	GameObject(std::string name);
	virtual ~GameObject();
	void init();
	void update();

	template<class T>
	T *getComponent();
	void addComponent(Component* component);

	void setPosition(glm::vec3 iposition);
	void setRotation(float irotation);

	glm::vec3 getPosition() { return position; }
	float getRotation() { return rotation; }
	//Used to keep track of all other objects in the game...
	//static std::vector<GameObject*> gameObjects;
	//static GameObject *find(std::string name);
	//static void cleanUpObjects();
	void destroy();
	void destroyObj(Object *object);

private:

	glm::vec3 position;
	float rotation;

	std::vector<Component *> componentList;
};

template<class T>
T *GameObject::getComponent()
{
	bool found = false;
	T *component = nullptr;
	int i = 0;
	while (!found)
	{
		//If the component has been found:
		if (component = dynamic_cast<T*>(componentList[i]))
			found = true;
		i++;
		//If we reach the end of the list:
		if (i == componentList.size())
			found = true;
	}
	return component;
}
