#include "openglRenderer.h"



OpenglUtils::lightStruct globalLight =
{
	{ 0.6f, 0.6f, 0.6f, 0.6f },		// ambient
	{ 0.5f, 0.5f, 0.5f, 0.5f },		// diffuse
	{ 0.04, 0.04, 0.04, 0.04f },	// specular
	{ 0.0f, 5.0f, 0.0f, 0.0f }		// position
};

OpenglUtils::materialStruct material1 = {
	{ 0.4f, 0.4f, 0.4f, 1.0f },		// ambient
	{ 0.8f, 0.8f, 0.8f, 1.0f },		// diffuse
	{ 0.04, 0.04, 0.04, 0.04 },		// specular
	0.5  // shininess
};

glm::vec4 lightPos;


// light attenuation
float attConstant = 1.0f;
float attLinear = 0.05f;
float attQuadratic = 0.01f;


void openglRenderer::setSceneLights()
{
	// set light attenuation shader uniforms
	GLuint uniformIndex = glGetUniformLocation(shaderProgram, "attConst");
	glUniform1f(uniformIndex, attConstant);
	uniformIndex = glGetUniformLocation(shaderProgram, "attLinear");
	glUniform1f(uniformIndex, attLinear);
	uniformIndex = glGetUniformLocation(shaderProgram, "attQuadratic");
	glUniform1f(uniformIndex, attQuadratic);

	OpenglUtils::setLight(shaderProgram, globalLight);

	OpenglUtils::setMaterial(shaderProgram, material1);

}

openglRenderer::openglRenderer()
{
	createWindow();
	setupRenderContext();

	init();
}

//Initialises camera values, view values, shaders and Enables some GL features needed (like DepthTest).
void openglRenderer::init()
{
	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);

	projection = glm::perspective(float(60.0f*DEG_TO_RADIAN), 800.0f / 600.0f, 1.0f, 150.0f);

	glm::mat4 modelview(1.0);
	mvStack.push(modelview);

	up = glm::vec3(0.0f, 1.0f, 0.0f);

	mvStack.top() = glm::lookAt(eye, at, up);

	shaderProgram = OpenglUtils::initShaders("minimal.vert", "minimal.frag");

	lightPos = glm::vec4(0.0f, 5.0f, 0.0f, 0.0f);


}

//for testing
void openglRenderer::lightControl()
{
	//lights

	//Temporary controls to help with render debugging
	const Uint8 *keys = SDL_GetKeyboardState(NULL);
	if (keys[SDL_SCANCODE_I]) lightPos.z -= 0.1;
	if (keys[SDL_SCANCODE_J])  lightPos.x -= 0.1;
	if (keys[SDL_SCANCODE_K]) lightPos.z += 0.1;
	if (keys[SDL_SCANCODE_L]) lightPos.x += 0.1;

	if (keys[SDL_SCANCODE_1]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glDisable(GL_CULL_FACE);
	}
	if (keys[SDL_SCANCODE_2]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glEnable(GL_CULL_FACE);
	}

	glm::vec4  tmp = mvStack.top()*lightPos;
	globalLight.position[0] = tmp.x;
	globalLight.position[1] = tmp.y;
	globalLight.position[2] = tmp.z;

	GLuint uniformIndex = glGetUniformLocation(shaderProgram, "lightPosition");
	glUniform4fv(uniformIndex, 1, globalLight.position);


}

//Camera Updates
void openglRenderer::update()
{
	//
	mvStack.top()*lightPos;
	setSceneLights();

	lightControl();
	//

	eye = camera->getEye();
	r = camera->getRotation();
	at = camera->getAt();

	mvStack.top() = glm::lookAt(eye, at, up);
}




void openglRenderer::draw(MeshComponent* mesh)
{
	update();


	//Draw code
	glUseProgram(shaderProgram);
	OpenglUtils::setUniformMatrix4fv(shaderProgram, "projection", glm::value_ptr(projection));

	glBindTexture(GL_TEXTURE_2D, mesh->getTextureID());
	mvStack.push(mvStack.top());

	mvStack.top() = glm::translate(mvStack.top(), mesh->getTranslation());
	mvStack.top() = glm::scale(mvStack.top(), mesh->getScaling());
	//mvStack.top() = glm::rotate(mvStack.top(), float(r*DEG_TO_RADIAN), eye);									//Need to introduce rotations, mainly for the player object to rotate with camera

	OpenglUtils::setUniformMatrix4fv(shaderProgram, "modelview", glm::value_ptr(mvStack.top()));
	//OpenglUtils::setMaterial(shaderProgram, mesh->getMaterial);												//Not using materials yet
	OpenglUtils::drawIndexedMesh(mesh->getMeshID(), mesh->getMeshIndexCount(), GL_TRIANGLES);
	mvStack.pop();

}



//Turns mesh data into a VBO
void openglRenderer::loadMesh(MeshComponent* mesh)
{
	GLuint meshObject = OpenglUtils::createMesh((GLuint)mesh->getNumVerts(), (GLfloat*)mesh->getVerts(), (GLfloat*)mesh->getColours(), (GLfloat*)mesh->getNorms(), (GLfloat*)mesh->getTexCoords(), (GLuint)mesh->getTexcoordCount(), (GLuint)mesh->getMeshIndexCount(), (GLuint*)mesh->getIndices());


	mesh->setMesh(meshObject);
}

//Generates a texture ID for a given filename
void openglRenderer::loadTexture(MeshComponent* mesh, char * filename)
{
	mesh->setTexture(SDLGLTextureLoader::loadBitmap(filename));
}

//Uses assimp to all the object data we need for creating a mesh VBO
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
	if (verts.empty())
		cout << "ERROR: mesh vertices not loaded" << endl;

}


//Defines the context and initialises GLEW
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

	cout << glGetString(GL_VERSION) << endl;											//Prints the openGL version in use

}

//initialises SDL and creates a window with openGL context
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

	glClearColor(1, 1, 0, 1);					//Sets glClearColour and uses GlClear to clear screen and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

