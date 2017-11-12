#include "openglRenderer.h"


openglRenderer::openglRenderer()
{
	std::cout << "glRenderer initialised" << std::endl;

	createWindow();
	setupRenderContext();

	init();
}

void openglRenderer::init()
{
	r = 0.0f;
	eye = glm::vec3(-2.0f, 1.0f, 8.0f);
	/*
	No compilation.
	Very odd runtime error happening when compiling shaders, needs fixed before any rendering can happen.
	*/

	shaderProgram = OpenglUtils::initShaders("minimal.vert", "minimal.frag");
}


void openglRenderer::update()
{
	
}


//this function is temporarily in here to help test rendering
glm::vec3 openglRenderer::moveForward(glm::vec3 pos, GLfloat angle, GLfloat d)
{
	return glm::vec3(pos.x + d*std::sin(r*DEG_TO_RADIAN), pos.y, pos.z - d*std::cos(r*DEG_TO_RADIAN));
}


glm::vec3 openglRenderer::moveRight(glm::vec3 pos, GLfloat angle, GLfloat d) {
	return glm::vec3(pos.x + d*std::cos(r*DEG_TO_RADIAN), pos.y, pos.z + d*std::sin(r*DEG_TO_RADIAN));
}

void openglRenderer::loadMesh(MeshComponent* mesh)
{
	GLuint meshObject = OpenglUtils::createMesh((GLuint)mesh->getNumVerts(), (GLfloat*)mesh->getVerts(), (GLfloat*)mesh->getColours(), (GLfloat*)mesh->getNorms(), (GLfloat*)mesh->getTexCoords(), (GLuint)mesh->getMeshIndexCount(), (GLuint*)mesh->getIndices());


	mesh->setMesh(meshObject);
}

void openglRenderer::loadTexture(MeshComponent* mesh, char * filename)
{
	mesh->setTexture(SDLGLTextureLoader::loadBitmap(filename));
}

void openglRenderer::loadObject(MeshComponent* mesh, const char * filename)
{
	//Temporary containers for object data
	std::vector<float> verts;
	std::vector<float> norms;
	std::vector<float> texCoords;
	std::vector<int>   indices;
	std::vector<float> colours;

	//Load objects into temporary containers
	AssimpLoader::loadObjectData(filename, verts, norms, texCoords, indices, colours);

	//Pass temporary containers into mesh to set the meshes values
	mesh->setMeshParameters(verts, norms, texCoords, indices, colours);

	

	//test values being produced by asssimp
	cout << "Number of Verts: " << mesh->getNumVerts() << endl;

	if (verts.empty())
	{
		cout << "ERROR: mesh vertices not loaded" << endl;
	}
	else
	{
		cout << "Mesh vertices  loaded" << endl;
	}
}


void openglRenderer::draw(MeshComponent* mesh)
{
	

	//Temporary controls to help with render debugging
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_W]) eye = moveForward(eye, r, 0.01f);
	if (keys[SDL_SCANCODE_S]) eye = moveForward(eye, r, -0.01f);
	if (keys[SDL_SCANCODE_A]) eye = moveRight(eye, r, -0.01f);
	if (keys[SDL_SCANCODE_D]) eye = moveRight(eye, r, 0.01f);
	if (keys[SDL_SCANCODE_R]) eye.y += 0.01;
	if (keys[SDL_SCANCODE_F]) eye.y -= 0.01;

	if (keys[SDL_SCANCODE_COMMA]) r -= 0.1f;
	if (keys[SDL_SCANCODE_PERIOD]) r += 0.1f;

	//View stuff
	stack<glm::mat4> mvStack;
	glm::mat4 projection(1.0);
	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);
	GLfloat scale(1.0f); 
	glm::mat4 modelview(1.0); 
	mvStack.push(modelview);
	glm::vec3 up(0.0f, 1.0f, 0.0f);
	glm::vec3 at = moveForward(eye, r, 1.0f);
	mvStack.top() = glm::lookAt(eye, at, up);

	//Draw code
	glUseProgram(shaderProgram);
	OpenglUtils::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	glBindTexture(GL_TEXTURE_2D, mesh->getTextureID());
	mvStack.push(mvStack.top());
	mvStack.top() = glm::translate(mvStack.top(), mesh->getTranslation());
	mvStack.top() = glm::scale(mvStack.top(), mesh->getScaling());
	OpenglUtils::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	//OpenglUtils::setMaterial(shaderProgram, mesh->getMaterial);
	OpenglUtils::drawIndexedMesh(mesh->getMeshID(), mesh->getMeshIndexCount(), GL_TRIANGLES);
	mvStack.pop();

	

}

void openglRenderer::setupRenderContext()
{
		
		//Request an OpenGL 3.0 context.
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	
		SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);										 // double buffering on
		SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);											 // 8 bit alpha buffering
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
		SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);									 // Turn on x4 multisampling anti-aliasing (MSAA)
															 	
		//Initialise glew, check init okay
		glewExperimental = GL_TRUE;
		GLenum err = glewInit();
		if (err != GLEW_OK)
			std::cout << "GLEW not initialized correctly" << std::endl;
		else
			std::cout << "GLEW initialised" << std::endl;

		cout << glGetString(GL_VERSION) << endl;											//Prints the openGL version in use

}

void openglRenderer::createWindow()
{
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)														//initialise SDL
	{
		std::cout << "SDL failed" << std::endl;
	}
	else
	{

		window = SDL_CreateWindow("iron rifts", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,	//createWindow(window title, pos on screen, pos on screan, width, height..)
			800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

		glContext = SDL_GL_CreateContext(window);
		SDL_GL_MakeCurrent(window, glContext);

		if (!window)			 // Check window was created OK
			std::cout << "Window not initialized correctly" << std::endl;											//Create window (inside class window)

																	//Create openGLs rendering context
	}

}

openglRenderer::~openglRenderer()
{
	delete this;
}


void openglRenderer::destroyWindow()
{
	SDL_GL_DeleteContext(glContext);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void openglRenderer::swapBuffers()
{
	SDL_GL_SwapWindow(window);
}

void openglRenderer::clearScreen()
{
	glEnable(GL_CULL_FACE);
	glClearColor(1, 1, 0, 1);					//Sets glClearColour and uses GlClear to clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

