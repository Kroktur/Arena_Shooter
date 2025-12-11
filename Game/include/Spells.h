#pragma once
#include "OgreSceneManager.h"

class Fireball
{
public:
    Fireball(Ogre::SceneManager* mgr, const Ogre::Vector3& pos, const Ogre::Vector3& dir);

    bool update(float dt);
    void destroy() const;

private:
    Ogre::SceneManager* m_manager;
    Ogre::SceneNode* m_node;
    Ogre::Item* m_item;

    Ogre::Vector3 m_direction;
    float m_speed;
    float m_lifetime;
};
