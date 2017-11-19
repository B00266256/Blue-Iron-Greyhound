#include "MeshComponent.h"
#include "OpenglRenderer.h"
#include "GameObject.h"

MeshComponent::MeshComponent(std::string name)
{
}

void MeshComponent::init()
{

}

void MeshComponent::update()
{
	renderer->draw(this);

	scaling = getUser()->getScaling();
	translation = getUser()->getTranslation();
	rotate = getUser()->getRenderRotate();
}

void MeshComponent::loadMesh()
{
	renderer->loadMesh(this);
}

void MeshComponent::loadTexture(char * filename)
{
	renderer->loadTexture(this, filename);
}

void MeshComponent::loadObject(const char * filename)
{
	renderer->loadObject(this, filename);
}

void MeshComponent::setRenderer(RenderingSystem* rendersystem)
{
	renderer = rendersystem;
}

void MeshComponent::setMeshParameters(vector<float> verts, vector<float> norms, vector<float> texCoords, vector<int> indices, vector<float> colours)
{
	this->verts = verts;
	this->norms = norms;
	this->texCoords = texCoords;
	this->indices = indices;
	this->colours = colours;
	this->meshIndexCount = indices.size();
	this->texCoordCount = texCoords.size();
	this->vertCount = verts.size();
}





void MeshComponent::setTranslation(glm::vec3 tran)
{
	translation = tran;
}

void MeshComponent::setScaling(glm::vec3 scale)
{
	scaling = scale;
}

int MeshComponent::getTexcoordCount()
{
	return texCoordCount;
}

glm::vec3 MeshComponent::getTranslation()
{
	return translation;
}

glm::vec3 MeshComponent::getRotate()
{
	return rotate;

}
glm::vec3 MeshComponent::getScaling()
{
	return scaling;
}

int MeshComponent::getMeshID()
{
	return meshID;
}

int MeshComponent::getMeshIndexCount()
{
	return meshIndexCount;
}

int MeshComponent::getTextureID()
{
	return textureID;
}

int MeshComponent::getNumVerts()
{
	return vertCount;
}
float* MeshComponent::getVerts()
{
	return verts.data();
}
float* MeshComponent::getNorms()
{
	return norms.data();
}
float* MeshComponent::getTexCoords()
{
	return texCoords.data();
}
int* MeshComponent::getIndices()
{
	return indices.data();
}
float* MeshComponent::getColours()
{
	return colours.data();
}


