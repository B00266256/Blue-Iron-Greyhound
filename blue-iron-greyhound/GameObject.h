#pragma once
#include <vector>
#include "Object.h"
#include "Component.h"
#include <glm/glm.hpp>

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
	void destroy();
	void destroyObj(Object *object);

	//Used to keep track of all other objects in the game...
	//static std::vector<GameObject*> gameObjects;
	//static GameObject *find(std::string name);
	//static void cleanUpObjects();
	void setCameraRotation(float rota) { cameraRotate = rota; }
	void setTranslation(glm::vec3 pos) { position = pos; }
	void setScaling(glm::vec3 scale) { scaling = scale; }
	void setRenderRotate(glm::vec3 rot) { meshRotate = rot; }

	glm::vec3 getTranslation() { return position; }
	glm::vec3 getScaling() { return scaling; }
	float getCameraRotation() { return cameraRotate; }
	glm::vec3 getRenderRotate() { return meshRotate; }
	//
	void input();
	//

protected:
	std::vector<Component *> componentList;

private:
	glm::vec3 position;
	glm::vec3 scaling;
	glm::vec3 meshRotate;			//for the rendering

	float cameraRotate;				//for the camera


};





template<class T>
T *GameObject::getComponent()
{
	bool found = false;
	T *component = nullptr;
	int i = 0;

	while (!found) {

		//Checks if we have found Component
		if (component = dynamic_cast<T*>(componentList[i]))
			found = true;

		i++;
		//Reached the end
		if (i == componentList.size())
			found = true;
	}
	return component;
}
