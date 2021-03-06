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
#include "Collisions.h"

//Temp includes for testing during development
#include "SDL.h"
#include <glm/glm.hpp>

//timer
#include <ctime>
#include <cstdlib>
#include "time.h"
// The number of clock ticks per second
#define CLOCKS_PER_SEC  ((clock_t)1000)
std::clock_t start;
double dt;


int main(int argc, char *argv[])
{
	//camera set up
	Camera *cameraComponent = new Camera(glm::vec3(-2.0f, 2.0f, 30.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, -1.0f), 0.0);
	cameraComponent->init();

	//render set up
	RenderingSystem* renderer = new openglRenderer();
	renderer->camera = cameraComponent;

	//Input System
	InputSystem *inputSystem = new SDLInputSystem();
	inputSystem->init();
	
	//collisions
	Collisions collision;
	

	//First Object - Acting as player (camera component / movement component)
	GameObject *Player = new GameObject("Collada");
	Player->setTranslation(glm::vec3(-5.0f, 0.0f, 60.0f));
	Player->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	Player->setCameraRotation(0.0);
	Player->setRenderRotateVec(glm::vec3(0, -1, 0));
	Player->setRenderRotateDeg(0);
	MeshComponent* meshComponent = new MeshComponent("sphere");
	Player->addComponent(meshComponent);
	meshComponent->setRenderer(renderer);
	meshComponent->loadObject("AlienPlanet2.dae");
	meshComponent->loadTexture("tex/scifiFloor.bmp");
	MovementComponent *moveComponent = new MovementComponent("moveComponent");
	moveComponent->setInput(inputSystem);
	
	Player->addComponent(cameraComponent);
	Player->addComponent(moveComponent);


	//Ground Plane
	GameObject *GroundPlane = new GameObject("Collada");
	GroundPlane->setTranslation(glm::vec3(0.0f, -5.0f, -30.0f));
	GroundPlane->setScaling(glm::vec3(60, 0.1f, 60));
	GroundPlane->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	MeshComponent* secondMesh = new MeshComponent("cube");
	GroundPlane->addComponent(secondMesh);
	secondMesh->setRenderer(renderer);
	secondMesh->loadObject("cube_with_2UVs.DAE");
	secondMesh->loadTexture("tex/rockyground.bmp");
	

	//Ground Plane 2
	GameObject *GroundPlane2 = new GameObject("Collada");
	GroundPlane2->setTranslation(glm::vec3(0.0f, -5.0f, 50.0f));
	GroundPlane2->setScaling(glm::vec3(60, 0.1f, 60));
	GroundPlane2->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	MeshComponent* secondMesh2 = new MeshComponent("cube");
	GroundPlane2->addComponent(secondMesh2);
	secondMesh2->setRenderer(renderer);
	secondMesh2->loadObject("cube_with_2UVs.DAE");
	secondMesh2->loadTexture("tex/rockyground.bmp");

	//Wall 1
	GameObject *walls = new GameObject("Collada");
	walls->setTranslation(glm::vec3(0.0f, 10.0f, -25.0f));
	walls->setScaling(glm::vec3(60, 0.5f, 60));
	walls->setRenderRotateVec(glm::vec3(1, 0, 0));
	walls->setRenderRotateDeg(90);
	MeshComponent* wallmesh = new MeshComponent("cube");
	walls->addComponent(wallmesh);
	wallmesh->setRenderer(renderer);
	wallmesh->loadObject("cube_with_2UVs.DAE");
	wallmesh->loadTexture("tex/scifi.bmp");
	
	//Wall 2
	GameObject *walls2 = new GameObject("Collada");
	walls2->setTranslation(glm::vec3(-60.0f, -50.0f, -25.0f));
	walls2->setScaling(glm::vec3(0.5f, 60, 60));
	walls2->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	MeshComponent* wallmesh2 = new MeshComponent("cube");
	walls2->addComponent(wallmesh2);
	wallmesh2->setRenderer(renderer);
	wallmesh2->loadObject("cube_with_2UVs.DAE");
	wallmesh2->loadTexture("tex/scifi.bmp");

	//Wall 2
	GameObject *walls3 = new GameObject("Collada");
	walls3->setTranslation(glm::vec3(60.0f, -50.0f, -25.0f));
	walls3->setScaling(glm::vec3(0.5f, 60, 60));
	walls3->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	MeshComponent* wallmesh3 = new MeshComponent("cube");
	walls3->addComponent(wallmesh3);
	wallmesh3->setRenderer(renderer);
	wallmesh3->loadObject("cube_with_2UVs.DAE");
	wallmesh3->loadTexture("tex/scifi.bmp");
	
	// Wall 4
	GameObject *walls4 = new GameObject("Collada");
	walls4->setTranslation(glm::vec3(60.0f, -50.0f, 80.0f));
	walls4->setScaling(glm::vec3(0.5f, 60, 60));
	walls4->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	MeshComponent* wallmesh4 = new MeshComponent("cube");
	walls4->addComponent(wallmesh4);
	wallmesh4->setRenderer(renderer);
	wallmesh4->loadObject("cube_with_2UVs.DAE");
	wallmesh4->loadTexture("tex/scifi.bmp");
	
	//Wall 5
	GameObject *walls5 = new GameObject("Collada");
	walls5->setTranslation(glm::vec3(-60.0f, -50.0f, 80.0f));
	walls5->setScaling(glm::vec3(0.5f, 60, 60));
	walls5->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	MeshComponent* wallmesh5 = new MeshComponent("cube");
	walls5->addComponent(wallmesh5);
	wallmesh5->setRenderer(renderer);
	wallmesh5->loadObject("cube_with_2UVs.DAE");
	wallmesh5->loadTexture("tex/scifi.bmp");

	//Wall 6
	GameObject *walls6 = new GameObject("Collada");
	walls6->setTranslation(glm::vec3(0.0f, 10.0f, 170.0f));
	walls6->setScaling(glm::vec3(60, 0.5f, 60));
	walls6->setRenderRotateVec(glm::vec3(1, 0, 0));
	walls6->setRenderRotateDeg(90);
	MeshComponent* wallmesh6 = new MeshComponent("cube");
	walls6->addComponent(wallmesh6);
	wallmesh6->setRenderer(renderer);
	wallmesh6->loadObject("cube_with_2UVs.DAE");
	wallmesh6->loadTexture("tex/scifi.bmp");
	

	


	//Research Building Object
	GameObject *buildingObject = new GameObject("old building");
	buildingObject->setTranslation(glm::vec3(-5.0f, -5.0f, 0.0f));
	buildingObject->setScaling(glm::vec3(3.0f, 3.0f, 3.0f));
	buildingObject->setRenderRotateVec(glm::vec3(-1.0f, 0.0f, 0.0f));
	buildingObject->setRenderRotateDeg(90);
	MeshComponent* buildingMesh = new MeshComponent("test");
	buildingObject->addComponent(buildingMesh);
	buildingMesh->setRenderer(renderer);
	buildingMesh->loadObject("building.dae");
	

	buildingMesh->loadTexture("tex/sandstoneWall1.bmp");
	buildingMesh->loadTexture("tex/tubes.bmp");
	buildingMesh->loadTexture("tex/building1.bmp");
	buildingMesh->loadTexture("tex/sandstoneWall1.bmp");
	buildingMesh->loadTexture("tex/sandstoneWall1.bmp");
	buildingMesh->loadTexture("tex/sandstoneWall1.bmp");
	buildingMesh->loadTexture("tex/sandstoneWall2.bmp");
	buildingMesh->loadTexture("tex/sandstoneWall2.bmp");
	buildingMesh->loadTexture("tex/tubes.bmp");
	buildingMesh->loadTexture("tex/tubes.bmp");
	buildingMesh->loadTexture("tex/fan1.bmp");
	buildingMesh->loadTexture("tex/satDish.bmp");
	buildingMesh->loadTexture("tex/building1.bmp");
	buildingMesh->loadTexture("tex/tubes.bmp");


	//watchtower
	GameObject *watchTower = new GameObject("watch tower");
	watchTower->setTranslation(glm::vec3(-40.0f, -5.0f, 70.0f));
	watchTower->setScaling(glm::vec3(4.0f, 4.0f, 4.0f));
	watchTower->setRenderRotateVec(glm::vec3(-1, 0, 0));
	watchTower->setRenderRotateDeg(90);
	MeshComponent* watchTowerMesh = new MeshComponent("test");
	watchTower->addComponent(watchTowerMesh);
	watchTowerMesh->setRenderer(renderer);
	watchTowerMesh->loadTexture("plainbuilding/iron.bmp");
	watchTowerMesh->loadObject("watchtower.dae");
	


	//TRASH PILE
	GameObject *trashPile = new GameObject("old building");
	trashPile->setTranslation(glm::vec3(40.0f, -5.0f, 30.0f));
	trashPile->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
	trashPile->setRenderRotateVec(glm::vec3(0, 0, 0));
	trashPile->setRenderRotateDeg(90);
	MeshComponent* trashmesh = new MeshComponent("test");
	trashPile->addComponent(trashmesh);
	trashmesh->setRenderer(renderer);
	trashmesh->loadObject("item01.obj");
	
	trashmesh->loadTexture("Trash/damagedwood.bmp");
	trashmesh->loadTexture("Trash/mossyConcrete.bmp");
	trashmesh->loadTexture("Trash/scratchedblue.bmp");
	trashmesh->loadTexture("Trash/stone.bmp");
	trashmesh->loadTexture("Trash/scratchedmetal.bmp");
	trashmesh->loadTexture("Trash/rustmetal.bmp");
	



	//road barrier
	GameObject *barrier = new GameObject("old building");
	barrier->setTranslation(glm::vec3(-20.0f, -5.0f, 90.0f));
	barrier->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
	barrier->setRenderRotateVec(glm::vec3(NULL, -NULL, NULL));
	MeshComponent* barriermesh = new MeshComponent("test");
	barrier->addComponent(barriermesh);
	barriermesh->setRenderer(renderer);
	barriermesh->loadObject("BARRIERE.obj");
	barriermesh->loadTexture("roadbarrier/BARRIERE.bmp");
	

	//road barrier
	GameObject *barrier2 = new GameObject("old building");
	barrier2->setTranslation(glm::vec3(0.0f, -5.0f, 90.0f));
	barrier2->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
	barrier2->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	MeshComponent* barriermesh2 = new MeshComponent("test");
	barrier2->addComponent(barriermesh2);
	barriermesh2->setRenderer(renderer);
	barriermesh2->loadObject("BARRIERE.obj");
	barriermesh2->loadTexture("roadbarrier/BARRIERE.bmp");

	GameObject *AlienPlanet = new GameObject("old building");
	AlienPlanet->setTranslation(glm::vec3(-200, 200, -300));
	AlienPlanet->setScaling(glm::vec3(50, 50, 50));
	AlienPlanet->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	MeshComponent* AlienPlanetMesh = new MeshComponent("test");
	AlienPlanet->addComponent(AlienPlanetMesh);
	AlienPlanetMesh->setRenderer(renderer);
	AlienPlanetMesh->loadObject("AlienPlanet2.dae");
	AlienPlanetMesh->loadTexture("tex/AlienPlanet.bmp");


	//Not showing needs a change of texture
	GameObject *AlienPlanet2 = new GameObject("old building");
	AlienPlanet2->setTranslation(glm::vec3(200, 200, -300));
	AlienPlanet2->setScaling(glm::vec3(50, 50, 50));
	AlienPlanet2->setRenderRotateVec(glm::vec3(NULL, NULL, NULL));
	MeshComponent* AlienPlanetMesh2= new MeshComponent("test");
	AlienPlanet2->addComponent(AlienPlanetMesh2);
	AlienPlanetMesh2->setRenderer(renderer);
	AlienPlanetMesh2->loadObject("AlienPlanet2.dae");
	AlienPlanetMesh2->loadTexture("tex/mercury.bmp");


	//Collisions
	//all dynamic objects will be tested against all static objects
	collision.addDynamicObject(Player);

	collision.addStaticObject(barrier2);
	collision.addStaticObject(barrier);
	collision.addStaticObject(walls);
	collision.addStaticObject(walls2);
	collision.addStaticObject(walls3);
	collision.addStaticObject(walls4);
	collision.addStaticObject(walls5); 
	collision.addStaticObject(walls6);
	collision.addStaticObject(trashPile);
	
	//collision.addStaticObject(buildingObject);
	collision.addStaticObject(watchTower);
	
	
	bool running = true;

	SDL_Event sdlEvent;
	do
	{
		//start timer 
		start = std::clock();

		while (SDL_PollEvent(&sdlEvent)) //This poll event should not be here since it couples the main to SDL. 
		{
			if (sdlEvent.type == SDL_QUIT)
			{
				running = false;
			}
		}

		renderer->clearScreen();

		//Player and Boundaries
		Player->update();
		GroundPlane->update();
		GroundPlane2->update();
		walls->update();
		walls2->update();
		walls3->update();
		walls4->update();
		walls5->update();
		walls6->update();

		//Buildings
		buildingObject->update();
		watchTower->update();
		
		//Misc
		barrier->update();
		barrier2->update();
		trashPile->update();
		AlienPlanet->update();
		AlienPlanet2->update();
		
		//Get Inputs - Temporary for free roam camera
		//Player->input(dt);

		

		//Check for Collisions
		collision.collisionSearch();

		renderer->swapBuffers();

		
 
		//Stores the time past the frame has taken to complete
		dt = (std::clock() - start) / (double)CLOCKS_PER_SEC;
	//	cout << dt << endl;
	} while (running);

	delete meshComponent;
	delete Player;
	delete renderer;
	delete GroundPlane;
	delete secondMesh;

	return 0;
}



/*
	GameObject *plainBuilding = new GameObject("old building");
	plainBuilding->setTranslation(glm::vec3(-15.0f, 1.0f, 50.0f));
	plainBuilding->setScaling(glm::vec3(5.0f, 5.0f, 5.0f));
	plainBuilding->setRenderRotate(glm::vec3(0, 0, 0));

	MeshComponent* plainBuildingMesh = new MeshComponent("test");
	plainBuilding->addComponent(plainBuildingMesh);
	plainBuildingMesh->setRenderer(renderer);
	//testmesh1->loadObject("plainbuilding.obj");
	
	//ground
	plainBuildingMesh->loadTexture("plainbuilding/brack.bmp");
	//lower windows
	plainBuildingMesh->loadTexture("plainbuilding/window1.bmp");
	//main windows
	plainBuildingMesh->loadTexture("plainbuilding/window2.bmp");
	//upper windows
	plainBuildingMesh->loadTexture("plainbuilding/window3.bmp");
	//??
	plainBuildingMesh->loadTexture("plainbuilding/wf.bmp");
	//brick
	plainBuildingMesh->loadTexture("plainbuilding/brack.bmp");
	//??
	plainBuildingMesh->loadTexture("plainbuilding/w2.bmp");
	//?/
	plainBuildingMesh->loadTexture("plainbuilding/store.bmp");
	//roof
	plainBuildingMesh->loadTexture("plainbuilding/top.bmp");
	//roof rim
	plainBuildingMesh->loadTexture("plainbuilding/top.bmp");
	//door 1
	plainBuildingMesh->loadTexture("plainbuilding/door.bmp");
	//door 2
	plainBuildingMesh->loadTexture("plainbuilding/door2.bmp");
	//ac
	plainBuildingMesh->loadTexture("plainbuilding/AC.bmp");
	//gutter pipe
	plainBuildingMesh->loadTexture("plainbuilding/iron.bmp");



	//Large Habitat Scene
	GameObject *habitat = new GameObject("test");
	habitat->setTranslation(glm::vec3(0.0f, -100.0f, 0.0f));
	habitat->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	habitat->setRenderRotate(glm::vec3(NULL, NULL, NULL));
	MeshComponent* habitatMesh = new MeshComponent("test");
	//testObject->addComponent(testMesh);
	habitatMesh->setRenderer(renderer);
	//testMesh->loadObject("habitat.obj");

	//benches	
	habitatMesh->loadTexture("tex/habitatWood.bmp");
	//buildings
	habitatMesh->loadTexture("tex/habitatBuilding2.bmp");
	//leaves
	habitatMesh->loadTexture("tex/habitatGrass.bmp");
	//lamps bulbs
	habitatMesh->loadTexture("tex/habitatBlack.bmp");
	//lamp posts
	habitatMesh->loadTexture("tex/habitatWeird.bmp");
	//paths/bridge
	habitatMesh->loadTexture("tex/habitatBuilding.bmp");
	//terrain
	habitatMesh->loadTexture("tex/habitatTerrain.bmp");
	//trees
	habitatMesh->loadTexture("tex/habitatWood2.bmp");
	//water
	habitatMesh->loadTexture("tex/habitatWater.bmp");
	//windows
	habitatMesh->loadTexture("tex/habitatWindow.bmp");

	*/