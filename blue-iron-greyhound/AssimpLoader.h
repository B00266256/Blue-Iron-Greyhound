#ifndef ASSIMPLOADER
#define ASSIMPLOADER

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

#include <vector>
using namespace std;

namespace AssimpLoader
{
	void loadObjectData(const std::string& file, std::vector<float> &verts, std::vector<float> &norms, std::vector<float> &texCoords, std::vector<int> &indices, std::vector<float> &colours);
	
}


#endif ASSIMPLOADER