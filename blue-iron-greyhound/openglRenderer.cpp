#include "openglRenderer.h"

openglRenderer:: openglRenderer(Window win)
{
	
	std::cout << "glRenderer initialised" << std::endl;
	createWindow(win);
	init();

}

void openglRenderer::init()
{
	
}

void openglRenderer::update()
{

}

void openglRenderer::setupRenderContext()
{
		
		//Request an OpenGL 3.0 context.
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);										 // double buffering on
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);											 // 8 bit alpha buffering
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);									 // Turn on x4 multisampling anti-aliasing (MSAA)
															 	
		//Initialise glew, check init okay
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
			std::cout << "GLEW not initialized correctly" << std::endl;
		else
			std::cout << "GLEW initialised" << std::endl;

		cout << glGetString(GL_VERSION) << endl;											//Prints the openGL version in use

}

void openglRenderer::createWindow(Window win)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)														//initialise SDL
	{
		std::cout << "SDL failed" << std::endl;
	}
	else
	{
		win.createWindow(800, 600, "Iron Rifts");											//Create window (inside class window)

		setupRenderContext();																//Create openGLs rendering context
	}

}

openglRenderer::~openglRenderer()
{
	delete this;
}