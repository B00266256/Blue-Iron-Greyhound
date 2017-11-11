/*=============================================================================
* Project: Blue Iron Greyhound
* 

commentcomment chloe
=============================================================================*/

#if _DEBUG
#pragma comment(linker, "/subsystem:\"console\" /entry:\"WinMainCRTStartup\"")
#endif

//#include "TestComponent.h"
//#include "InteractiveTestComponent.h"
#include "OpenglRenderer.h"
#include "GameObject.h"

//Temp includes for testing during development
#include "SDL.h"
#include <glm/glm.hpp>

class RenderingSystem;




int main(int argc, char *argv[])
{

	
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

	GameObject *firstObject = new GameObject("Collada Cube");

	MeshComponent* meshComponent = new MeshComponent("First Mesh");
	meshComponent->setRenderer(renderer);
	meshComponent->loadObject("cube.dae");
	meshComponent->loadMesh();
	meshComponent->loadTexture("fabric.bmp");
	meshComponent->setTranslation(glm::vec3(-10.0f, -0.1f, -10.0f));
	meshComponent->setScaling(glm::vec3(0.05, 0.05, 0.05));

	firstObject->addComponent(meshComponent);
	


	bool running = true;
	
	SDL_Event sdlEvent;
	do 
	{
		while (SDL_PollEvent(&sdlEvent)) //This poll event should not be here since it couples the main to SDL. 
		{				
			if (sdlEvent.type == SDL_QUIT)
			{
				running = false;
			}
		}

		firstObject->update();
		
		
	} while (running);

	delete meshComponent;
	delete firstObject;

	return 0;
}