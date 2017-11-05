
#include "SDL.h"
#include <GL/glew.h>
#include <string>
#include <iostream>


#ifndef window_H
#define window_H
#pragma once

class Window
{
public:
	void createWindow(int width, int height, char* title);				//Creates window to draw onto
	void destroyWindow();												//Destroys context and window
	void swapBuffers();													//Called at the end of each frame
	void clearScreen();

private:
	SDL_Window* window;													//Window Handle
	SDL_GLContext glContext;											//Context Handle

};
#endif