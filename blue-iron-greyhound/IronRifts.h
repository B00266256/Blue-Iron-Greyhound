
#include "openglRenderer.h"
#include "window.h"
/*
This class will probably be at the centre of everything
*/

#ifndef IronRifts_H
#define IronRifts_H
#pragma once
class IronRifts
{
public:

	IronRifts();
	void draw();
	void update();

	void gameLoop();


private:
	bool running;
	Window window;
	glm::mat4 projection;
	glm::vec3 eye;
	glm::vec3 up;
	glm::vec3 at;
	
	openglRenderer *renderer;
	
};
#endif