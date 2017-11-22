/*=============================================================================
* InputSystem.h
* Author: Adam Stanton
* Abstract parent for input handling systems...
=============================================================================*/

#pragma once
#include "System.h"
#include <string>

class InputSystem : public System
{
public:
	InputSystem() {};
	virtual ~InputSystem() {};

	virtual void init() = 0;
	virtual bool keyPressed(std::string key) = 0;
	//Need a mouse function!!!!
};