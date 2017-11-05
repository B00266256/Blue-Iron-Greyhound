#include "openglRenderer.h"


openglRenderer:: openglRenderer()
{
	
	std::cout << "glRenderer initialised" << std::endl;
	createWindow();
	setupRenderContext();
	init();

}

void openglRenderer::init()
{
	
}



void openglRenderer::update()
{

}

void openglRenderer::draw()
{
	clearScreen();


	swapBuffers();

}

void openglRenderer::setupRenderContext()
{
		
		//Request an OpenGL 3.0 context.
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
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

void openglRenderer::createWindow()
{
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)														//initialise SDL
	{
		std::cout << "SDL failed" << std::endl;
	}
	else
	{

		window = SDL_CreateWindow("iron rifts", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,	//createWindow(window title, pos on screen, pos on screan, width, height..)
			800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

		glContext = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, glContext);

		if (!window)			 // Check window was created OK
			std::cout << "Window not initialized correctly" << std::endl;											//Create window (inside class window)

																	//Create openGLs rendering context
	}

}

openglRenderer::~openglRenderer()
{
	delete this;
}


void openglRenderer::destroyWindow()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void openglRenderer::swapBuffers()
{
	SDL_GL_SwapWindow(window);
}

void openglRenderer::clearScreen()
{
	glClearColor(1, 1, 0, 1);					//Sets glClearColour and uses GlClear to clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT);
}

