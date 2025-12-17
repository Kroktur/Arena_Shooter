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
        ofbx::IScene* scene = nullptr;
    };
Ogre::Item* createItemFromFBX(Ogre::SceneManager* sceneMgr, const ofbx::Mesh* mesh, int meshIdx);
Ogre::Item* getMaterialFromFBX(Ogre::Item* item, const ofbx::Mesh* mesh, int meshIdx, GraphicsSystem* mgraphsy);


// Load the FBX file into an ofbx::IScene pointer (caller owns destroy())
//ofbx::IScene* loadFBXFile(const std::string& filepath);

// Extract submeshes (one FBXSubMesh per material/partition)
//std::vector<FBXSubMesh> extractMeshes(ofbx::IScene* scene);
}

struct FBXParsedData {
    ofbx::IScene* scene;
    std::vector<const ofbx::Mesh*> meshes;
};

class FBXReader
{
public:
    FBXReader() = default;
    ~FBXReader() = default;

    // Load FBX file into memory
    static std::vector<uint8_t> loadFile(const char* path);

    // Extract position, rotation and scale from FBX matrix
    static void extractTransform(const ofbx::DMatrix& matrix, Ogre::Vector3& position,
        Ogre::Quaternion& rotation, Ogre::Vector3& scale);
};

#endif
