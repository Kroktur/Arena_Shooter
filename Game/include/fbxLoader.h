#ifndef FBXLOADER
#define FBXLOADER
#include <string>
#include <vector>
#include "ofbx.h"
#include "utils.h"
#include "GraphicsSystem.h"
#include "OgreSceneManager.h"
#include "OgreItem.h"
#include <filesystem>
struct loadMap
{
    struct info {
        Ogre::Item* item;
        Ogre::SceneNode* node;
    };
    static std::vector<info> CreateFromFBX(Ogre::SceneManager *m_manager, Demo::GraphicsSystem *mGraphicSystem, std::string filePath)
    {
		std::filesystem::path GlobalPath = "../../../Media/FBXFile/";
		GlobalPath += filePath;
		std::string pathStr = GlobalPath.string();
		const char* fbxPath = pathStr.c_str();
		auto fileData = loadFile(fbxPath);
		ofbx::IScene* scene = ofbx::load(fileData.data(), (ofbx::usize)fileData.size(), static_cast<ofbx::u16>(ofbx::LoadFlags::NONE), nullptr, nullptr);

		std::vector<info> result;
		if (!scene)
			throw std::runtime_error("Failed to parse FBX file");

		int loadedCount = 0;
		int meshc = scene->getMeshCount();
		for (int i = 0; i < meshc; i++)
		{
			const ofbx::Mesh* mesh = scene->getMesh(i);
			Ogre::Item* item = createItemFromFBX(m_manager, mesh, i);
			if (item)
			{
				//getMaterialFromFBX(item, mesh, i, mGraphicsSystem);
				Ogre::SceneNode* node = m_manager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
					->createChildSceneNode(Ogre::SCENE_DYNAMIC);

				ofbx::DMatrix globalTransform = mesh->getGlobalTransform();

				Ogre::Vector3 position;
				Ogre::Quaternion rotation;
				Ogre::Vector3 scale;

				loadMap::extractTransform(globalTransform, position, rotation, scale);

				node->setPosition(position);
				node->setOrientation(rotation);
				node->setScale(scale);
				node->attachObject(item);

				result.push_back({ item,node});
	

				loadedCount++;
			}
		}

		if (loadedCount == 0)
			throw std::runtime_error("No valid meshes found in FBX");
		scene->destroy();
		return result;
    }
	static Ogre::Item* createItemFromFBX(Ogre::SceneManager* sceneMgr, const ofbx::Mesh* mesh, int meshIdx);
	static Ogre::Item* getMaterialFromFBX(Ogre::Item* item, const ofbx::Mesh* mesh, int meshIdx, Demo::GraphicsSystem* mgraphsy);
	static std::vector<uint8_t> loadFile(const char* path);

	// Extract position, rotation and scale from FBX matrix
	static void extractTransform(const ofbx::DMatrix& matrix, Ogre::Vector3& position,
		Ogre::Quaternion& rotation, Ogre::Vector3& scale);
};


struct FBXParsedData {
    ofbx::IScene* scene;
    std::vector<const ofbx::Mesh*> meshes;
};


#endif
