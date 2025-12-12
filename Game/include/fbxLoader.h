#ifndef FBXLOADER
#define FBXLOADER
#include <string>
#include <vector>
#include "ofbx.h"
#include "utils.h"
#include "GraphicsSystem.h"

namespace Demo {
    class FBXSubMesh : public GraphicsSystem {

    public:
        std::string name;
        std::vector<float> positions;
        std::vector<float> normals;
        std::vector<float> uvs;
        std::vector<uint32_t> indices;
    };
Ogre::Item* createItemFromFBX(Ogre::SceneManager* sceneMgr, const ofbx::Mesh* mesh, int meshIdx);

// Load the FBX file into an ofbx::IScene pointer (caller owns destroy())
//ofbx::IScene* loadFBXFile(const std::string& filepath);

// Extract submeshes (one FBXSubMesh per material/partition)
//std::vector<FBXSubMesh> extractMeshes(ofbx::IScene* scene);
}
#endif
