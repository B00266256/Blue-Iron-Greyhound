#include "window.h"


void Window::createWindow(int width, int height,char* title)
{
	
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,	//createWindow(window title, pos on screen, pos on screan, width, height..)
		width, height, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	glContext = SDL_GL_CreateContext(window);
	SDL_GL_MakeCurrent(window, glContext);

	if (!window)			 // Check window was created OK
		std::cout << "Window not initialized correctly" << std::endl;
}


void Window::destroyWindow()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Window::swapBuffers()
{
	SDL_GL_SwapWindow(window);
}