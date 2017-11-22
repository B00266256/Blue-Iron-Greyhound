/*=============================================================================
* SDLInputSystem.h
* Author: Adam Stanton
* Uses SDL to deal with user input using the keyboard and mouse...
=============================================================================*/

#pragma once
#include "InputSystem.h"
#include <SDL.h>
#include <string>
#include <map>

typedef std::pair<std::string, unsigned int> keys;

class SDLInputSystem : public InputSystem
{
public:
	SDLInputSystem();
	virtual ~SDLInputSystem();

	void init();
	bool keyPressed(std::string);
	//Need a mouse function!!!!
private:
	std::map<std::string, unsigned int> keyMap;
};