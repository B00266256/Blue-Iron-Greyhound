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

	//First Object
	GameObject *firstObject = new GameObject("Collada Cube");

	MeshComponent* meshComponent = new MeshComponent("First Mesh");
	meshComponent->setRenderer(renderer);
	meshComponent->loadObject("cubeUV.dae");
	meshComponent->loadTexture("fabric.bmp");
	meshComponent->loadMesh();
	meshComponent->setTranslation(glm::vec3(-10.0f, -0.1f, -10.0f));
	//meshComponent->setScaling(glm::vec3(0.05, 0.05, 0.05));
	meshComponent->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));

	firstObject->addComponent(meshComponent);
	
	//Second Object
	GameObject *secondObject = new GameObject("Collada Cube");

	MeshComponent* secondMesh = new MeshComponent("First Mesh");
	secondMesh->setRenderer(renderer);
	secondMesh->loadObject("cubeUV.dae");
	secondMesh->loadTexture("fabric.bmp");
	secondMesh->loadMesh();
	secondMesh->setTranslation(glm::vec3(-10.0f, -1.1f, -10.0f));
	//meshComponent->setScaling(glm::vec3(0.05, 0.05, 0.05));
	secondMesh->setScaling(glm::vec3(20.0f, 1.0f, 20.0f));
	secondObject->addComponent(secondMesh);

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

		renderer->clearScreen();

		firstObject->update();
		secondObject->update();

		renderer->swapBuffers();
		
		
	} while (running);

	delete meshComponent;
	delete firstObject;

	return 0;
}