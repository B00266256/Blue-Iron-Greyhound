#pragma once
#pragma once
#include <vector>
#include <glm/glm.hpp>
#include "GameObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include "OpenglUtils.h"
#include <glm/gtc/type_ptr.hpp>
#include "System.h"

#include "RigidBodyComponent.h"
class RigidBodyComponent;
#include <GL/glew.h>
#define DEG_TO_RADIAN 0.017453293

class CollisionSystem : public System
{
public:
	void init();
	
	void collisionCheck(RigidBodyComponent* rigidbody);

	void addStaticBody(RigidBodyComponent* rigidbody);
	void addDynamicBody(RigidBodyComponent* rigidbody);

	void addBody(RigidBodyComponent* rigidbody);

	void searchCollisions(RigidBodyComponent* rigidbody);


	bool AABBtoAABB(glm::vec3 min1, glm::vec3 max1, glm::vec3 min2, glm::vec3 max2);

private:
	std::vector<RigidBodyComponent*> staticBodies;

	std::vector<RigidBodyComponent*> dynamicBodies;


	std::vector<glm::vec3> staticMins;
	std::vector<glm::vec3> staticMaxs;


	//
	glm::vec3 prevPosition;
	//
};