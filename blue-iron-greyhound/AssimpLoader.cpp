#include "AssimpLoader.h"
using namespace std;
#include <iostream>


namespace AssimpLoader
{
	
	//Extracts all the data we need and puts into into our parameters
	void loadObjectData(const std::string& file, std::vector<float> &verts, std::vector<float> &norms, std::vector<float> &texCoords, std::vector<int> &indices, std::vector<float> &colours)
	{
		//const aiScene *scene = importFile(file);

		// Create an instance of the Importer class for loading the object data
		Assimp::Importer importer;


		//loads our file into a scene object so its all accessible.
		const aiScene* scene = importer.ReadFile(file,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);




		if (!scene)
		{
			std::cout << "ERROR: Assimp file load failed." << std::endl;
			const char * 	GetErrorString();
			return;
		}

		const aiMesh* mesh = scene->mMeshes[0];

		//if (mesh == NULL)
		//	return;


		int numOfFaces = mesh->mNumFaces;
		int numOfIndices = numOfFaces * 3;
		

		for (unsigned int i = 0; i < mesh->mNumFaces; ++i) {
			const aiFace &face = mesh->mFaces[i];
			indices.push_back(face.mIndices[0]);
			indices.push_back(face.mIndices[1]);
			indices.push_back(face.mIndices[2]);
		}

		int numOfVertices = mesh->mNumVertices;
		
		for (unsigned int i = 0; i < mesh->mNumVertices; ++i) {
			if (mesh->HasPositions()) {
				verts.push_back(mesh->mVertices[i].x);
				verts.push_back(mesh->mVertices[i].y);
				verts.push_back(mesh->mVertices[i].z);

			}

			if (mesh->HasNormals()) {
				norms.push_back(mesh->mNormals[i].x);
				norms.push_back(mesh->mNormals[i].x);
				norms.push_back(mesh->mNormals[i].x);
		
			}

			if (mesh->HasTextureCoords(0)) {
				texCoords.push_back(mesh->mTextureCoords[0][i].x);
				texCoords.push_back(mesh->mTextureCoords[0][i].y);
			}
		}
	}
	



	//This imports our objects data into a 'scene' object which holds are the information. This 'scene' is passed to 
	//LoadObjectData() function above which actually extracts the relevant data we need.
	const aiScene * importFile(const std::string& pFile)
	{
		// Create an instance of the Importer class for loading the object data
		Assimp::Importer importer;

	
		//loads our file into a scene object so its all accessible.
		const aiScene* scene = importer.ReadFile(pFile,
			aiProcess_CalcTangentSpace |
			aiProcess_Triangulate |
			aiProcess_JoinIdenticalVertices |
			aiProcess_SortByPType);


		return scene;

	}





}