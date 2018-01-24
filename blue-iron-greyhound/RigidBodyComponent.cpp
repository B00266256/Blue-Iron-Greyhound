#include "RigidBodyComponent.h"
#include "GameObject.h"


//Specify the type of bounding box but it will only be created when a mesh is given to the rigid bodys user. The mesh will access the rigid 
//body and create and initliased according to defined bodyType (AABB or Sphere at this point).
RigidBodyComponent::RigidBodyComponent(string name)
{
	this->name = name;
	init();
}



void RigidBodyComponent::init()
{
	//bodyType = "STATIC";
	isAsleep = false;
	isInitialised = false;

	
}

boundingVolume* RigidBodyComponent::getBoundingVolume()
{
	return boundingVolume;
}


void RigidBodyComponent::update()
{
	

	//create bounding volume if not done already
	//if (!isInitialised)
	//{
	//	boundingType = "AABB"; 

	//	//get vales from mesh/vertice loading
	//	//createAABB(getUser()->getMin(), getUser()->getMax());

	//	
	//	boundingVolume->update(pos);

	//	isInitialised = true;
	//}

	//If dynamic update the bounding volumes position
	if (bodyType == "DYNAMIC")
	{
		boundingVolume->update(getUser()->getPosition());
	}


}


//sets values for the boudning volume
// if the bounding volume is a sphere then one point is treated as center and the other point a point on the circumference of the circle
void RigidBodyComponent::setboundingVolume(glm::vec3 p1, glm::vec3 p2)
{
	glm::vec3 pos = getUser()->getPosition();

	if (bodyType == "AABB")
	{
		createAABB(p1, p2);
		boundingVolume->update(pos);
	}
	else if (bodyType == "SPHERE")
	{
		createSphere(p1, glm::distance(p1, p2));
		boundingVolume->update(pos);
	}
	else
	{
		createAABB(p1, p2);
		boundingVolume->update(pos);
	}

	isInitialised = true;
}


void RigidBodyComponent::createAABB(glm::vec3 min, glm::vec3 max)
{
	boundingType = "AABB";
	boundingVolume = new AABB(min, max);
	isInitialised = true;
	collisionSystem->addBody(this);
}


void RigidBodyComponent::createSphere(glm::vec3 center, float radius)
{
	boundingType = "SPHERE";
	boundingVolume = new Sphere(center, radius);
	isInitialised = true;
	collisionSystem->addBody(this);
}


void RigidBodyComponent::setBodyType(string bodytype)
{
	bodyType = bodytype;

	if (bodyType == "DYNAMIC")
	{
		collisionSystem->addDynamicBody(this);
	}
	if (bodyType == "STATIC")
	{
		collisionSystem->addStaticBody(this);
	}



	collisionSystem->addBody(this);
}

string RigidBodyComponent::getBodyType()
{
	return bodyType;
}

string RigidBodyComponent::getBoundingType()
{
	return boundingType;
}

bool RigidBodyComponent::isInit()
{
	return isInitialised;
}




RigidBodyComponent::~RigidBodyComponent()
{
	delete boundingVolume;
}

  




