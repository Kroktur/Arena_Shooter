#pragma once
#include <OgreSceneManager.h>
#include "ObjectPull.h"

namespace NodePull
{
    using Type = ObjectPull<Ogre::SceneNode, 64>;

    static auto destroy = [](Ogre::SceneNode* node, Ogre::SceneManager* manager) ->void
        {
            if (!node || !manager)
                return;

            manager->destroySceneNode(node);
        };

    static auto create = [](Ogre::SceneManager* manager)-> Ogre::SceneNode*
        {
            return manager->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
        };

    static auto reset = [](Ogre::SceneNode* node) ->void
        {
            node->setPosition(Ogre::Vector3::ZERO);
            node->setOrientation(Ogre::Quaternion::IDENTITY);
            node->setScale(Ogre::Vector3::UNIT_SCALE);
        };
}