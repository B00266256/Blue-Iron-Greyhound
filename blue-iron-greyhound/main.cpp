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
#include "MovementComponent.h"
#include "SDLInputSystem.h"

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

	//
	InputSystem *inputSystem = new SDLInputSystem();
	inputSystem->init();
	//
	





	//First Object - Acting as player
	GameObject *firstObject = new GameObject("Collada");
	firstObject->setTranslation(glm::vec3(-5.0f, 0.0f, 0.0f));
	firstObject->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	firstObject->setCameraRotation(0.0);
	firstObject->setRenderRotate(glm::vec3(NULL, NULL, NULL));

	MeshComponent* meshComponent = new MeshComponent("sphere");
	meshComponent->setRenderer(renderer);
	meshComponent->loadObject("sphere_triangulate.dae");
	meshComponent->loadTexture("scifiFloor.bmp");

	MovementComponent *moveComponent = new MovementComponent("moveComponent");
	moveComponent->setInput(inputSystem);
	

	firstObject->addComponent(meshComponent);
	firstObject->addComponent(cameraComponent);
	firstObject->addComponent(moveComponent);


	//Ground Plane
	GameObject *secondObject = new GameObject("Collada");
	secondObject->setTranslation(glm::vec3(0.0f, 0.0f, -50.0f));
	secondObject->setScaling(glm::vec3(120, 1.0f, 120));
	secondObject->setRenderRotate(glm::vec3(NULL, NULL, NULL));

	MeshComponent* secondMesh = new MeshComponent("cube");
	secondMesh->setRenderer(renderer);
	secondMesh->loadObject("cube_with_2UVs.DAE");
	secondMesh->loadTexture("sand.bmp");


	secondObject->addComponent(secondMesh);


	//Duck Object
	GameObject *duck = new GameObject("Collada");
	duck->setTranslation(glm::vec3(-10.0f, 0.1f, 0.0f));
	duck->setScaling(glm::vec3(0.02f, 0.02f, 0.02f));
	duck->setRenderRotate(glm::vec3(NULL, NULL, NULL));

	MeshComponent* duckMesh = new MeshComponent("Duck");
	duckMesh->setRenderer(renderer);
	duckMesh->loadObject("duck_triangulate.DAE");
	duckMesh->loadTexture("scifiFloor.bmp");
	

	duck->addComponent(duckMesh);



	//building Object
	GameObject *buildingObject = new GameObject("old building");
	buildingObject->setTranslation(glm::vec3(-5.0f, 0.0f, 0.0f));
	buildingObject->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	buildingObject->setRenderRotate(glm::vec3(-1.0f, 0.0f, 0.0f));

	MeshComponent* buildingMesh = new MeshComponent("test");
	buildingMesh->setRenderer(renderer);
	buildingMesh->loadObject("old_building.dae");
	buildingMesh->loadTexture("scifiFloor.bmp");
	

	buildingObject->addComponent(buildingMesh);

	//Large Habitat Scene
	GameObject *testObject = new GameObject("test");
	testObject->setTranslation(glm::vec3(0.0f, -100.0f, 0.0f));
	testObject->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	testObject->setRenderRotate(glm::vec3(NULL, NULL, NULL));

	MeshComponent* testMesh = new MeshComponent("test");
	testMesh->setRenderer(renderer);
	testMesh->loadObject("habitat.obj");

	//benches	
	testMesh->loadTexture("habitatWood.bmp");
	//buildings
	testMesh->loadTexture("habitatBuilding2.bmp");
	//leaves
	testMesh->loadTexture("habitatGrass.bmp");
	//lamps bulbs
	testMesh->loadTexture("habitatBlack.bmp");
	//lamp posts
	testMesh->loadTexture("habitatWeird.bmp");
	//paths/bridge
	testMesh->loadTexture("habitatBuilding.bmp");
	//terrain
	testMesh->loadTexture("habitatTerrain.bmp");
	//trees
	testMesh->loadTexture("habitatWood2.bmp");
	//water
	testMesh->loadTexture("habitatWater.bmp");
	//windows
	testMesh->loadTexture("habitatWindow.bmp");
	

	
	
	
	
	
	
	
	

	

	

	
	
	
	
	

	

	testObject->addComponent(testMesh);







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
		duck->update();

		buildingObject->update();

		testObject->update();

	

		renderer->swapBuffers();


	} while (running);

	delete meshComponent;
	delete firstObject;
	delete renderer;
	delete secondObject;
	delete secondMesh;

	return 0;
}