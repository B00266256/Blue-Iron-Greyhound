#include "IronRifts.h"

IronRifts::IronRifts()
{

	projection = glm::mat4(1.0);
	eye = glm::vec3(-2.0f, 1.0f, 8.0f);
	up = glm::vec3(0.0f, 1.0f, 0.0f);
	at = glm::vec3(0.0f, 1.0f, -1.0f);
	
	renderer = new openglRenderer(window);

	gameLoop();

}

void IronRifts::draw()
{
	
	window.clearScreen();																//Sets glClearColour and uses GlClear to clear screen and depth buffer

	/*
	Draw in here
	This will probably call a class that is defining our game
	Like Scene.draw();
	*/

	window.swapBuffers();
}

void IronRifts::update()
{
	// Poll input events
	//This section should be replaced by our input handler. Need it now for the SDL window to work.
	///
	SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
		{
			window.destroyWindow();
			running = false;
		}
	}
	///
	
}

void IronRifts::gameLoop()
{
	running = true;

	while (running)
	{		
		update();
		draw();
	}

	window.destroyWindow();					//Game no longer running so destroy everything.
}