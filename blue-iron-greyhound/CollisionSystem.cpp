#include "CollisionSystem.h"
#include "AABB.h"


void CollisionSystem::init() 
{

}

void CollisionSystem::collisionCheck(RigidBodyComponent* rigidbody)
{
	searchCollisions(rigidbody);
}



void CollisionSystem::searchCollisions(RigidBodyComponent* rigidbody)
{
	//go through all possible static collisions

	//go through all possible collisions with other moving bodiesvh 
	

}

bool CollisionSystem::AABBtoAABB(glm::vec3 min1, glm::vec3 max1, glm::vec3 min2, glm::vec3 max2)
{
	// Collision tests. if any tests are false then theres no intersection.
	if (max1.x < min2.x || min1.x > max2.x)
		return false;
	if (max1.y < min2.y || min1.y > max2.y)
		return false;
	if (max1.z < min2.z || min1.z > max2.z)
		return false;
	else
		return true;

}


void CollisionSystem::addStaticBody(RigidBodyComponent* rigidbody)
{
	staticBodies.push_back(rigidbody);
}

void CollisionSystem::addDynamicBody(RigidBodyComponent* rigidbody)
{
	dynamicBodies.push_back(rigidbody);
}





void CollisionSystem::addBody(RigidBodyComponent* rigidbody)
{
	string bounding = rigidbody->getBodyType();



}
