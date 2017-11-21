/*=============================================================================
* Object.h
* Author: Adam Stanton
* Abstract parent to our entire component/object architecture...
=============================================================================*/

#pragma once
#include <string>

using namespace std;

class Object
{
public:

	Object() {};
	virtual ~Object() {};

	virtual void init() = 0;
	virtual void update() = 0;
	virtual void destroy() = 0;
	virtual void destroyObj(Object *object) = 0;

	string getName() { return name; }
	int getInstanceID() { return instanceID; }
protected:
	 string name;
	 int instanceID;
};