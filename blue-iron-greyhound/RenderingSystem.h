#pragma once

#include "Component.h"
class MeshComponent;

#ifndef RenderingSystem_H
#define RenderingSystem_H
#pragma once

class RenderingSystem : public Component
{
public:
	RenderingSystem() {}
	virtual ~RenderingSystem() {};

	virtual void init() = 0;
	virtual void update() = 0;

	virtual void swapBuffers() = 0;
	virtual void clearScreen() = 0;

	virtual void draw(MeshComponent* mesh) = 0;
	virtual void loadMesh(MeshComponent* meshComponent) = 0;
	virtual void loadTexture(MeshComponent* meshComponent,  char * fileName) = 0;
	virtual void loadObject(MeshComponent* mesh, const char * filename) = 0;
private:

	

};
#endif