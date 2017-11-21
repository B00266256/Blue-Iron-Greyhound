/*=============================================================================
* Project: Blue Iron Greyhound
* Authors: Adam Stanton, Chloe Madden, Paul McGlauchlan, Thomas Mackrell (Kinda)
=============================================================================*/

#include "TestComponent.h"
#include "InteractiveTestComponent.h"
#include "MovementComponent.h"
#include "SDLInputSystem.h"

SDL_Window* setupRC(SDL_GLContext & context)
{
	SDL_Window * window;
	if (SDL_Init(SDL_INIT_VIDEO) < 0) // Initialize video
	{
		std::cout << "Unable to initialize SDL";
		exit(1);
	}
	// Request an OpenGL 3.0 context.
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);  // double buffering on
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8); // 8 bit alpha buffering
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4); // Turn on x4 multisampling anti-aliasing (MSAA)

													   // Create 800x600 window
	window = SDL_CreateWindow("SDL/GLM/OpenGL Demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
	if (!window) // Check window was created OK
	{
		std::cout << "Unable to initialize Window";
		exit(1);
	}
	context = SDL_GL_CreateContext(window); // Create opengl context and attach to window
	SDL_GL_SetSwapInterval(1); // set swap buffers to sync with monitor's vertical refresh rate
	return window;
}

int main(int argc, char *argv[])
{
	SDL_Window * hWindow; // window handle
	SDL_GLContext glContext; // OpenGL context handle
	hWindow = setupRC(glContext); // Create window and render context 

	SDL_Event sdlEvent;		//Variable to detect SDL events.


	InputSystem *inputSystem = new SDLInputSystem();
	inputSystem->init();

	GameObject *testObj = new GameObject("testObj");
	TestComponent *testComponentA = new TestComponent("testComponentA");
	InteractiveTestComponent *testComponentB = new InteractiveTestComponent("testComponentB");
	MovementComponent *moveComponent = new MovementComponent("moveComponent");
	moveComponent->setInput(inputSystem);

	//testObj->addComponent(testComponentA);
	//testObj->addComponent(testComponentB);
	testObj->addComponent(moveComponent);
	
	testObj->init();
	//testObj->update();

	testObj->setRotation(0.0f);

	//testObj->getComponent<MovementComponent>()->moveForward();
	//testObj->getComponent<MovementComponent>()->moveForward();
	//testObj->getComponent<MovementComponent>()->moveBackwards();
	
	//testObj->update();
	//testObj->getComponent<MovementComponent>()->moveLeft();
	//testObj->getComponent<MovementComponent>()->moveBackwards();
	//testObj->getComponent<MovementComponent>()->moveLeft();
	//testObj->getComponent<MovementComponent>()->moveLeft();
	//testObj->getComponent<MovementComponent>()->moveRight();
	//testObj->getComponent<MovementComponent>()->moveRight();

	//testObj->getComponent<InteractiveTestComponent>()->update();


	int i = 1;
	do 
	{ 
		

		while (SDL_PollEvent(&sdlEvent))
		{
			if (sdlEvent.type == SDL_QUIT)	//If the user quits:
				i = 0;			//End the loop.
		}

		testObj->update(); 
	
	} while (i != 0);

	return 0;
}