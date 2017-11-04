#pragma once

#include "Component.h"

#ifndef RenderingSystem_H
#define RenderingSystem_H
#pragma once

class RenderingSystem : public Component
{
public:
	RenderingSystem() {}
	RenderingSystem(Window win) {}
	virtual ~RenderingSystem() {};

	virtual void init() = 0;
	virtual void update() = 0;

	

private:

	

};
#endif