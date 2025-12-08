#pragma once
#include <OgreSceneManager.h>
#include "ObjectPull.h"

class NodePpull : public ObjectPull<Ogre::SceneNode, 64>
{
public:
	static void Init(Ogre::SceneManager* manager)
	{
		m_manager = manager;
	}
private:
	Ogre::SceneNode* Create() override
	{
		return m_manager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
			->createChildSceneNode(Ogre::SCENE_DYNAMIC);
	}
	void Reset(int index) override
	{
		auto& node = m_allNode[index];
		node->setPosition(Ogre::Vector3::ZERO);
		node->setOrientation(Ogre::Quaternion::IDENTITY);
		node->setScale(Ogre::Vector3::UNIT_SCALE);
	}
	void Destroy(Ogre::SceneNode* node) override
	{
		m_manager->destroySceneNode(node);
	}
	static Ogre::SceneManager* m_manager;
};

inline Ogre::SceneManager* NodePpull::m_manager = nullptr;

static inline NodePpull& NodePpullSingleton()
{
	static NodePpull sd;
	return sd;
}