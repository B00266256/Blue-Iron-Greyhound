/*=============================================================================
* Project: Blue Iron Greyhound
* 

commentcomment chloe
=============================================================================*/

#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

#include "TestComponent.h"
#include "InteractiveTestComponent.h"
#include "openglRenderer.h"

#include "SDL.h"




int main(int argc, char *argv[])
{

	//IronRifts game;
	RenderingSystem* renderer = new openglRenderer();

	/*GameObject *testObj = new GameObject("testObj");
	TestComponent *testComponentA = new TestComponent("testComponentA");
	InteractiveTestComponent *testComponentB = new InteractiveTestComponent("testComponentB");

	testObj->addComponent(testComponentA);
	testObj->addComponent(testComponentB);
	
	testObj->init();
	testObj->update();
	testObj->getComponent<InteractiveTestComponent>()->update();
	testObj->update();
	*/
	int i = 1;
	
	SDL_Event sdlEvent;
	do 
	{
		while (SDL_PollEvent(&sdlEvent)) {				//This poll event should not be here since it couples the main to SDL. 
			if (sdlEvent.type == SDL_QUIT)
				i = 0;
		}

		renderer->draw();
	
	} while (i != 0);



	return 0;
}