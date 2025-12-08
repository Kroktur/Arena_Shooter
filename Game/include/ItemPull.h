#pragma once

#include <OgreMesh2.h>
#include <OgreSceneManager.h>
#include "ObjectPull.h"
#include "OgreItem.h"
#include "OgreSceneNode.h"

namespace ItemPull
{

	using Type = ObjectPull<Ogre::Item, 16>;

    static auto destroy = [](Ogre::Item* node, Ogre::SceneManager* manager) ->void
        {
            if (!node || !manager)
                return;
            manager->destroyItem(node);
        };

    static auto create = [](Ogre::SceneManager* manager,const std::string& name)-> Ogre::Item*
        {
            return manager->createItem(
                name, Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
                Ogre::SCENE_DYNAMIC);


        };

    static auto reset = [](Ogre::Item* node) ->void
        {
			return;
        };


    static auto conditionRacoon = [](Ogre::Item* node) -> bool
        {
            return node->getMesh()->getName() == "Plane.mesh";
        };
    static auto conditionCube = [](Ogre::Item* node) -> bool
        {
            return node->getMesh()->getName() == "CubeFromMedia_d.mesh";
        };
}