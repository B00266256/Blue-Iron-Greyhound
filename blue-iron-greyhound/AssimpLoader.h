#ifndef ASSIMPLOADER
#define ASSIMPLOADER

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>           // Output data structure
#include <assimp/postprocess.h>     // Post processing fla

#include <vector>
using namespace std;

namespace AssimpLoader
{
	void loadObjectData(const std::string& file, vector<int>& meshIDs, vector<int> &indexCount);
	
}


#endif ASSIMPLOADER