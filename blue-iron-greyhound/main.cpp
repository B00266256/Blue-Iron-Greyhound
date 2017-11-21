/*=============================================================================
* Project: Blue Iron Greyhound
* 

commentcomment chloe
=============================================================================*/

#include "TestComponent.h"
#include "InteractiveTestComponent.h"
<<<<<<< HEAD
=======
#include "openglRenderer.h"

#include "SDL.h"



>>>>>>> origin/master

int main(int argc, char *argv[])
{
	int i = 0; //test
	GameObject *testObj = new GameObject("testObj");
	TestComponent *testComponentA = new TestComponent("testComponentA");
	InteractiveTestComponent *testComponentB = new InteractiveTestComponent("testComponentB");

<<<<<<< HEAD
=======
	//IronRifts game;
	RenderingSystem* renderer = new openglRenderer();

	/*GameObject *testObj = new GameObject("testObj");
	TestComponent *testComponentA = new TestComponent("testComponentA");
	InteractiveTestComponent *testComponentB = new InteractiveTestComponent("testComponentB");

>>>>>>> origin/master
	testObj->addComponent(testComponentA);
	testObj->addComponent(testComponentB);
	
	testObj->init();
	testObj->update();
	testObj->getComponent<InteractiveTestComponent>()->update();
	testObj->update();
<<<<<<< HEAD

	int i = 1;
	do {} while (i != 0);
=======
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


>>>>>>> origin/master

	return 0;
}