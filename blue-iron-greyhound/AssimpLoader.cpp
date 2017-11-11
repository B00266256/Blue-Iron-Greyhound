#include "AssimpLoader.h"
using namespace std;
#include <iostream>


namespace AssimpLoader
{
	
	//Extracts all the data we need and puts into into our parameters
	void loadObjectData(const std::string& file, std::vector<float> &verts, std::vector<float> &norms, std::vector<float> &texCoords, std::vector<int> &indices, std::vector<float> &colours)
	{
		const aiScene *sc = importFile(file);

		const aiMesh* mesh = sc->mMeshes[0];

		// create array with faces
		// have to convert from Assimp format to array
		unsigned int *faceArray;
		faceArray = (unsigned int *)malloc(sizeof(unsigned int) * mesh->mNumFaces * 3);
		unsigned int faceIndex = 0;

		for (unsigned int t = 0; t < mesh->mNumFaces; ++t) {
			const aiFace* face = &mesh->mFaces[t];

			memcpy(&faceArray[faceIndex], face->mIndices, 3 * sizeof(unsigned int));
			faceIndex += 3;
		}

		int faces = sc->mMeshes[0]->mNumFaces;

		
		//load verts
		int nVertices = mesh->mNumVertices;
	
		for (int i = 0; i < mesh->mNumVertices; i++)
		{
			float verticeX = mesh->mVertices[i].x;
			float verticeY = mesh->mVertices[i].y;
			float verticeZ = mesh->mVertices[i].z;

			verts.push_back(verticeX);
			verts.push_back(verticeY);
			verts.push_back(verticeZ);

			float normX = mesh->mNormals[i].x;
			float normY = mesh->mNormals[i].y;
			float normZ = mesh->mNormals[i].z;

			norms.push_back(normX);
			norms.push_back(normY);
			norms.push_back(normZ);

			if (mesh->HasTextureCoords(i))
			{
				float texCoordsX = mesh->mTextureCoords[0][i].x;
				float texCoordsY = mesh->mTextureCoords[0][i].y;

				texCoords.push_back(normY);
				texCoords.push_back(normZ);
			}
			
		}

		if (!verts.empty())
		{
			std::cout << "Object Vertices Loaded" << std::endl;
		}
		else
		{
			std::cout << "ERROR: Object Vertices not loaded" << std::endl;
		}


	

		//load colours
		for (int j = 0; j < mesh->mNumVertices; j++)
		{

					colours.push_back(1);
					colours.push_back(1);
					colours.push_back(1);
					//colours.push_back(1);
				
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


		//Lets us know if the file import failed.
		if (!scene)
		{
			std::cout << "ERROR: Assimp file load failed." << std::endl;
			return false;
		}

		// Now we can access the file's contents. 

		//cout << scene->mNumMeshes << endl;
		//cout << scene->mNumMaterials << endl;
		//cout << scene->mNumAnimations << endl;
		//cout << scene->mNumTextures << endl;



		/*if (scene->HasMeshes())
		{
			cout << "Has Meshes" << endl;
		}*/


		//loadObjectData(scene);

	
		return scene;

	}





}