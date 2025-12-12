#include "Spells.h"
#include <OgreItem.h>
#include <OgreMovableObject.h>


Fireball::Fireball(Ogre::SceneManager* mgr, const Ogre::Vector3& pos, const Ogre::Vector3& dir)
	: m_manager(mgr), m_direction(dir.normalisedCopy()), m_speed(300.0f), m_lifetime(2.0f)
{
	m_node = m_manager->getRootSceneNode()->createChildSceneNode();
	m_node->setPosition(pos);
	m_item = m_manager->createItem("Plane.mesh");
	m_node->attachObject(m_item);
}

bool Fireball::update(float dt)
{
    m_lifetime -= dt;
    if (m_lifetime <= 0)
        return false;

    m_node->translate(m_direction * m_speed * dt, Ogre::Node::TS_WORLD);
    m_node->yaw(Ogre::Degree(360 * dt));

    return true;
}

void Fireball::destroy() const
{
    m_node->detachAllObjects();
    m_manager->destroyItem(m_item);
    m_manager->destroySceneNode(m_node);
}