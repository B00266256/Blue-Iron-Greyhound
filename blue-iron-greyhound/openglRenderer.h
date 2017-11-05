#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>

#include <SDL.h>
#include <GL/glew.h>
#include <iostream>


#include "RenderingSystem.h"

#ifndef openglRenderer_H
#define openglRenderer_H
#pragma once

class openglRenderer : public RenderingSystem
{
public: 

	
	openglRenderer();
	~openglRenderer();

	void init();
	void update();
	void draw();

	void createWindow();					//initialises SDL and creates a window with openGL context
	void setupRenderContext();				//Defines the context and initialises GLEW

	void destroyWindow();
	void swapBuffers();
	void clearScreen();
	
private:
	SDL_Window* window;												//Window Handle
	SDL_GLContext glContext;										//Context Handle

	//perspective variables
	//Not used right now. Probably won't be used in this class
	std::stack<glm::mat4> mvStack;
	glm::mat4 proj;
	glm::mat4 modelview;
	glm::vec3 eye;
	glm::vec3 up;
	glm::vec3 at;
};
#endif