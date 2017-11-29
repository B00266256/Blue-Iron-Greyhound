#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OpenglUtils.h"
#include <glm/gtc/type_ptr.hpp>

#include <GL/glew.h>
#define DEG_TO_RADIAN 0.017453293

class Collisions
{
public:

	//checks for intersection for all the dynamic objects against all the static objects 
	void AABBtoAABB();

	// not working. This was supposed to draw bounding boxes for ease of debugging
	void draw(); 

	//Methods for adding objects 
	void addStaticObject(GameObject* object);
	void addDynamicObject(GameObject* object);
private:
	std::vector<GameObject*> staticObjects;
	std::vector<GameObject*> dynamicObjects;

	std::vector<glm::vec3> staticMins;
	std::vector<glm::vec3> staticMaxs;

	std::vector<glm::vec3> dynMins;
	std::vector<glm::vec3> dynMaxs;
};