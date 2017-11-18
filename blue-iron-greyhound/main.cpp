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
#include "CameraComponent.h"

//Temp includes for testing during development
#include "SDL.h"
#include <glm/glm.hpp>

class RenderingSystem;




int main(int argc, char *argv[])
{

	
	

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

	//camera set up
	Camera *cameraComponent = new Camera(glm::vec3(-2.0f, 1.0f, 8.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0);
	cameraComponent->init();
	
	//render set up
	RenderingSystem* renderer = new openglRenderer();
	renderer->camera = cameraComponent;


	//First Object - Acting as player
	GameObject *firstObject = new GameObject("Collada");
	firstObject->setTranslation(glm::vec3(-5.0f, 1.0f, 0.0f));
	firstObject->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	firstObject->setCameraRotation(0.0);
	firstObject->setRenderRotate(glm::vec3(1, 1, 1));

	MeshComponent* meshComponent = new MeshComponent("sphere");
	meshComponent->setRenderer(renderer);
	meshComponent->loadObject("sphere_triangulate.dae");
	meshComponent->loadTexture("scifiFloor.bmp");
	meshComponent->loadMesh();
	
	firstObject->addComponent(meshComponent);
	firstObject->addComponent(cameraComponent);
	

	//Ground Plane
	GameObject *secondObject = new GameObject("Collada");
	secondObject->setTranslation(glm::vec3(-1.0f, -1.1f, -25.0f));
	secondObject->setScaling(glm::vec3(20.0f, 1.0f, 20.0f));
	secondObject->setRenderRotate(glm::vec3(1, 1, 1));

	MeshComponent* secondMesh = new MeshComponent("cube");
	secondMesh->setRenderer(renderer);
	secondMesh->loadObject("cube_with_2UVs.DAE");
	secondMesh->loadTexture("scifi.bmp");
	secondMesh->loadMesh();
	
	secondObject->addComponent(secondMesh);


	//Duck Object
	GameObject *duck = new GameObject("Collada");
	duck->setTranslation(glm::vec3(-10.0f, 0.1f, 0.0f));
	duck->setScaling(glm::vec3(0.02f, 0.02f, 0.02f));
	duck->setRenderRotate(glm::vec3(1, 1, 1));

	MeshComponent* duckMesh = new MeshComponent("Duck");
	duckMesh->setRenderer(renderer);
	duckMesh->loadObject("duck_triangulate.DAE");
	duckMesh->loadTexture("scifiFloor.bmp");
	duckMesh->loadMesh();
	
	duck->addComponent(duckMesh);
	



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

		//
		firstObject->input();
		//

		firstObject->update();
		secondObject->update();
		duck->update();

		renderer->swapBuffers();
		
		
	} while (running);

	delete meshComponent;
	delete firstObject;
	delete renderer;
	delete secondObject;
	delete secondMesh;

	return 0;
}