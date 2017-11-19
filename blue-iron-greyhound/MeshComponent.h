#ifndef MESHCOMPONENT
#define MESHCOMPONENT

#include <glm/glm.hpp>
#include <vector>
#include "Component.h"
#include "RenderingSystem.h"
using namespace std;


class MeshComponent : public Component
{
public:
	MeshComponent(std::string name);
	~MeshComponent() {}

	void init();
	void update();

	void loadMesh();
	void loadTexture(char * filename);
	void loadObject(const char * filename);

	//Gets
	glm::vec3 getTranslation();
	glm::vec3 getScaling();
	glm::vec3 getRotate();
	int getMeshID();

	int getNumVerts();
	float* getVerts();
	float* getNorms();
	float* getTexCoords();
	int* getIndices();
	float* getColours();
	int getMeshIndexCount();
	int getTexcoordCount();
	int getTextureID();

	//Sets
	void setMesh(int ID) { meshID = ID; }
	void setTexture(int ID) { textureID = ID; }
	void setRenderer(RenderingSystem* rendersystem);
	void setMeshParameters(vector<float> verts, vector<float> norms, vector<float> texCoords, vector<int> indices, vector<float> colours);
	void setTranslation(glm::vec3 tran);
	void setScaling(glm::vec3 scale);

	RenderingSystem *renderer;
private:
	//transformation data for renderer
	glm::vec3 translation;
	glm::vec3 scaling;
	glm::vec3 rotate;


	//3D object data
	std::vector<float> verts;
	std::vector<float> norms;
	std::vector<float> texCoords;
	std::vector<int> indices;
	std::vector<float> colours;
	int vertCount;
	int meshIndexCount;
	int texCoordCount;

	int meshID;
	int textureID;
	//int material...


};
#endif