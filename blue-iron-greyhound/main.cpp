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

//timer
#include <ctime>
#include <cstdlib>
#include "time.h"
// The number of clock ticks per second
#define CLOCKS_PER_SEC  ((clock_t)1000)

class RenderingSystem;


#include "Collisions.h"


std::clock_t start;
double dt;


int main(int argc, char *argv[])
{
	//camera set up
	Camera *cameraComponent = new Camera(glm::vec3(-2.0f, 1.0f, 30.0f), glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), 0.0);
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
	Player->setRenderRotate(glm::vec3(NULL, NULL, NULL));
	MeshComponent* meshComponent = new MeshComponent("sphere");
	Player->addComponent(meshComponent);
	meshComponent->setRenderer(renderer);
	meshComponent->loadObject("sphere_triangulate.dae");
	meshComponent->loadTexture("tex/scifiFloor.bmp");
	MovementComponent *moveComponent = new MovementComponent("moveComponent");
	moveComponent->setInput(inputSystem);
	
	
	Player->addComponent(cameraComponent);
	//Player->addComponent(moveComponent);


	//Ground Plane
	GameObject *GroundPlane = new GameObject("Collada");
	GroundPlane->setTranslation(glm::vec3(0.0f, -5.0f, -30.0f));
	GroundPlane->setScaling(glm::vec3(60, 0.1f, 60));
	GroundPlane->setRenderRotate(glm::vec3(NULL, NULL, NULL));
	MeshComponent* secondMesh = new MeshComponent("cube");
	GroundPlane->addComponent(secondMesh);
	secondMesh->setRenderer(renderer);
	secondMesh->loadObject("cube_with_2UVs.DAE");
	secondMesh->loadTexture("tex/rockyground.bmp");
	

	//Ground Plane 2
	GameObject *GroundPlane2 = new GameObject("Collada");
	GroundPlane2->setTranslation(glm::vec3(0.0f, -5.0f, 50.0f));
	GroundPlane2->setScaling(glm::vec3(60, 0.1f, 60));
	GroundPlane2->setRenderRotate(glm::vec3(NULL, NULL, NULL));
	MeshComponent* secondMesh2 = new MeshComponent("cube");
	GroundPlane2->addComponent(secondMesh2);
	secondMesh2->setRenderer(renderer);
	secondMesh2->loadObject("cube_with_2UVs.DAE");
	secondMesh2->loadTexture("tex/rockyground.bmp");



	//Wall 1
	GameObject *walls = new GameObject("Collada");
	walls->setTranslation(glm::vec3(0.0f, 10.0f, -25.0f));
	walls->setScaling(glm::vec3(60, 0.5f, 60));
	walls->setRenderRotate(glm::vec3(1, 0, 0));
	MeshComponent* wallmesh = new MeshComponent("cube");
	walls->addComponent(wallmesh);
	wallmesh->setRenderer(renderer);
	wallmesh->loadObject("cube_with_2UVs.DAE");
	wallmesh->loadTexture("tex/scifi.bmp");
	

	//Wall 2
	GameObject *walls2 = new GameObject("Collada");
	walls2->setTranslation(glm::vec3(-60.0f, -50.0f, -25.0f));
	walls2->setScaling(glm::vec3(0.5f, 60, 60));
	walls2->setRenderRotate(glm::vec3(NULL, NULL, NULL));
	MeshComponent* wallmesh2 = new MeshComponent("cube");
	walls2->addComponent(wallmesh2);
	wallmesh2->setRenderer(renderer);
	wallmesh2->loadObject("cube_with_2UVs.DAE");
	wallmesh2->loadTexture("tex/scifi.bmp");


	//Wall 2
	GameObject *walls3 = new GameObject("Collada");
	walls3->setTranslation(glm::vec3(60.0f, -50.0f, -25.0f));
	walls3->setScaling(glm::vec3(0.5f, 60, 60));
	walls3->setRenderRotate(glm::vec3(NULL, NULL, NULL));
	MeshComponent* wallmesh3 = new MeshComponent("cube");
	walls3->addComponent(wallmesh3);
	wallmesh3->setRenderer(renderer);
	wallmesh3->loadObject("cube_with_2UVs.DAE");
	wallmesh3->loadTexture("tex/scifi.bmp");
	

	// Wall 4
	GameObject *walls4 = new GameObject("Collada");
	walls4->setTranslation(glm::vec3(60.0f, -50.0f, 80.0f));
	walls4->setScaling(glm::vec3(0.5f, 60, 60));
	walls4->setRenderRotate(glm::vec3(NULL, NULL, NULL));
	MeshComponent* wallmesh4 = new MeshComponent("cube");
	walls4->addComponent(wallmesh4);
	wallmesh4->setRenderer(renderer);
	wallmesh4->loadObject("cube_with_2UVs.DAE");
	wallmesh4->loadTexture("tex/scifi.bmp");
	

	//Wall 5
	GameObject *walls5 = new GameObject("Collada");
	walls5->setTranslation(glm::vec3(-60.0f, -50.0f, 80.0f));
	walls5->setScaling(glm::vec3(0.5f, 60, 60));
	walls5->setRenderRotate(glm::vec3(NULL, NULL, NULL));
	MeshComponent* wallmesh5 = new MeshComponent("cube");
	walls5->addComponent(wallmesh5);
	wallmesh5->setRenderer(renderer);
	wallmesh5->loadObject("cube_with_2UVs.DAE");
	wallmesh5->loadTexture("tex/scifi.bmp");


	//Wall 6
	GameObject *walls6 = new GameObject("Collada");
	walls6->setTranslation(glm::vec3(0.0f, 10.0f, 170.0f));
	walls6->setScaling(glm::vec3(60, 0.5f, 60));
	walls6->setRenderRotate(glm::vec3(1, 0, 0));
	MeshComponent* wallmesh6 = new MeshComponent("cube");
	walls6->addComponent(wallmesh6);
	wallmesh6->setRenderer(renderer);
	wallmesh6->loadObject("cube_with_2UVs.DAE");
	wallmesh6->loadTexture("tex/scifi.bmp");
	

	


	//Research Building Object
	GameObject *buildingObject = new GameObject("old building");
	buildingObject->setTranslation(glm::vec3(-5.0f, -5.0f, 0.0f));
	buildingObject->setScaling(glm::vec3(3.0f, 3.0f, 3.0f));
	buildingObject->setRenderRotate(glm::vec3(-1.0f, 0.0f, 0.0f));

	
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
	watchTower->setRenderRotate(glm::vec3(-1, 0, 0));

	MeshComponent* watchTowerMesh = new MeshComponent("test");
	watchTower->addComponent(watchTowerMesh);
	watchTowerMesh->setRenderer(renderer);
	watchTowerMesh->loadTexture("plainbuilding/iron.bmp");
	watchTowerMesh->loadObject("watchtower.dae");
	


	//TRASH PILE
	GameObject *test = new GameObject("old building");
	test->setTranslation(glm::vec3(40.0f, -5.0f, 30.0f));
	test->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
	test->setRenderRotate(glm::vec3(0, 0, 0));

	MeshComponent* testmesh = new MeshComponent("test");
	test->addComponent(testmesh);
	testmesh->setRenderer(renderer);
	testmesh->loadObject("item01.obj");
	
	testmesh->loadTexture("Trash/damagedwood.bmp");
	testmesh->loadTexture("Trash/mossyConcrete.bmp");
	testmesh->loadTexture("Trash/scratchedblue.bmp");
	testmesh->loadTexture("Trash/stone.bmp");
	testmesh->loadTexture("Trash/scratchedmetal.bmp");
	testmesh->loadTexture("Trash/rustmetal.bmp");
	


	GameObject *test1 = new GameObject("old building");
	test1->setTranslation(glm::vec3(-15.0f, 1.0f, 50.0f));
	test1->setScaling(glm::vec3(5.0f, 5.0f, 5.0f));
	test1->setRenderRotate(glm::vec3(0, 0, 0));

	MeshComponent* testmesh1 = new MeshComponent("test");
	test1->addComponent(testmesh1);
	testmesh1->setRenderer(renderer);
	//testmesh1->loadObject("plainbuilding.obj");
	
	//ground
	testmesh1->loadTexture("plainbuilding/brack.bmp");
	//lower windows
	testmesh1->loadTexture("plainbuilding/window1.bmp");
	//main windows
	testmesh1->loadTexture("plainbuilding/window2.bmp");
	//upper windows
	testmesh1->loadTexture("plainbuilding/window3.bmp");
	//??
	testmesh1->loadTexture("plainbuilding/wf.bmp");
	//brick
	testmesh1->loadTexture("plainbuilding/brack.bmp");
	//??
	testmesh1->loadTexture("plainbuilding/w2.bmp");
	//?/
	testmesh1->loadTexture("plainbuilding/store.bmp");
	//roof
	testmesh1->loadTexture("plainbuilding/top.bmp");
	//roof rim
	testmesh1->loadTexture("plainbuilding/top.bmp");
	//door 1
	testmesh1->loadTexture("plainbuilding/door.bmp");
	//door 2
	testmesh1->loadTexture("plainbuilding/door2.bmp");
	//ac
	testmesh1->loadTexture("plainbuilding/AC.bmp");
	//gutter pipe
	testmesh1->loadTexture("plainbuilding/iron.bmp");


	//old wood building
	GameObject *test2 = new GameObject("old building");
	test2->setTranslation(glm::vec3(-80.0f, -5.0f, 80.0f));
	test2->setScaling(glm::vec3(0.05f, 0.05f, 0.05f));
	test2->setRenderRotate(glm::vec3(0, 0, 0));

	MeshComponent* testmesh2 = new MeshComponent("test");
	test2->addComponent(testmesh2);
	testmesh2->setRenderer(renderer);
	testmesh2->loadTexture("tex/scifiFloor.bmp");
	testmesh2->loadObject("OLD house.obj");
	

	//Large Habitat Scene
	GameObject *testObject = new GameObject("test");
	testObject->setTranslation(glm::vec3(0.0f, -100.0f, 0.0f));
	testObject->setScaling(glm::vec3(1.0f, 1.0f, 1.0f));
	testObject->setRenderRotate(glm::vec3(NULL, NULL, NULL));
	MeshComponent* testMesh = new MeshComponent("test");
	//testObject->addComponent(testMesh);
	testMesh->setRenderer(renderer);
	//testMesh->loadObject("habitat.obj");

	//benches	
	testMesh->loadTexture("tex/habitatWood.bmp");
	//buildings
	testMesh->loadTexture("tex/habitatBuilding2.bmp");
	//leaves
	testMesh->loadTexture("tex/habitatGrass.bmp");
	//lamps bulbs
	testMesh->loadTexture("tex/habitatBlack.bmp");
	//lamp posts
	testMesh->loadTexture("tex/habitatWeird.bmp");
	//paths/bridge
	testMesh->loadTexture("tex/habitatBuilding.bmp");
	//terrain
	testMesh->loadTexture("tex/habitatTerrain.bmp");
	//trees
	testMesh->loadTexture("tex/habitatWood2.bmp");
	//water
	testMesh->loadTexture("tex/habitatWater.bmp");
	//windows
	testMesh->loadTexture("tex/habitatWindow.bmp");



	//road barrier
	GameObject *barrier = new GameObject("old building");
	barrier->setTranslation(glm::vec3(-20.0f, -5.0f, 90.0f));
	barrier->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
	barrier->setRenderRotate(glm::vec3(0, -1, 0));
	MeshComponent* barriermesh = new MeshComponent("test");
	barrier->addComponent(barriermesh);
	barriermesh->setRenderer(renderer);
	barriermesh->loadObject("BARRIERE.obj");
	barriermesh->loadTexture("roadbarrier/BARRIERE.bmp");
	

	//road barrier
	GameObject *barrier2 = new GameObject("old building");
	barrier2->setTranslation(glm::vec3(0.0f, -5.0f, 90.0f));
	barrier2->setScaling(glm::vec3(0.5f, 0.5f, 0.5f));
	barrier2->setRenderRotate(glm::vec3(NULL, NULL, NULL));
	MeshComponent* barriermesh2 = new MeshComponent("test");
	barrier2->addComponent(barriermesh2);
	barriermesh2->setRenderer(renderer);
	barriermesh2->loadObject("BARRIERE.obj");
	barriermesh2->loadTexture("roadbarrier/BARRIERE.bmp");



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
	collision.addStaticObject(test);
	collision.addStaticObject(test1);
	
	
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

		Player->update();
		GroundPlane->update();
		GroundPlane2->update();

		buildingObject->update();
		
		barrier->update();
		barrier2->update();

		watchTower->update();
		walls->update();
		walls2->update();
		walls3->update();
		walls4->update();
		walls5->update();
		walls6->update();

		test->update();
		test1->update();
		//test2->update();

	
		collision.AABBtoAABB();
			

		Player->input(dt);

		renderer->swapBuffers();



		dt = (std::clock() - start) / (double)CLOCKS_PER_SEC;

		//cout << dt << endl;

	} while (running);

	delete meshComponent;
	delete Player;
	delete renderer;
	delete GroundPlane;
	delete secondMesh;

	return 0;
}