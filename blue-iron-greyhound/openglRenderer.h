#ifndef openglRenderer_H
#define openglRenderer_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stack>
#include <SDL.h>
#include <GL/glew.h>
#include <iostream>

#include "RenderingSystem.h"
#include "MeshComponent.h"

#include "AssimpLoader.h"
#include "OpenglUtils.h"
#include "SDLGLTextureLoader.h"


#define DEG_TO_RADIAN 0.017453293


class openglRenderer : public RenderingSystem
{
public: 

	
	openglRenderer();
	~openglRenderer();

	void init();
	void update();
	void draw(MeshComponent* mesh);
	void loadMesh(MeshComponent* mesh);
	void loadTexture(MeshComponent* mesh,  char * filename);
	void loadObject(MeshComponent* mesh, const char * filename);

	void createWindow();					//initialises SDL and creates a window with openGL context
	void setupRenderContext();				//Defines the context and initialises GLEW

	void destroyWindow();
	void swapBuffers();
	void clearScreen();

	

	//Temporary until this is put in its own class. Probably a transform class or something
	glm::vec3 moveForward(glm::vec3 pos, GLfloat angle, GLfloat d);
	glm::vec3 moveRight(glm::vec3 pos, GLfloat angle, GLfloat d);
private:
	SDL_Window* window;												//Window Handle
	SDL_GLContext glContext;										//Context Handle

	GLuint shaderProgram;

	GLfloat r;
	glm::vec3 eye;
	glm::vec3 at;
	glm::vec3 up;
	glm::mat4 projection;

	stack<glm::mat4> mvStack;
};
#endif