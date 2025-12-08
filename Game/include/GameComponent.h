#pragma once
#include "Core/Component.h"
#include "ItemPull.h"
template<typename Entity>
class LivingComponent : public KT::Component<Entity>
{
public:
	LivingComponent() : KT::Component<Entity>(),m_isLiving(true){}
	void EnableDeath()
	{
		m_isLiving = false;
	}
	void StopDeath()
	{
		m_isLiving = true;
	}
	bool IsLiving()
	{
		return m_isLiving;
	}
private:
	bool m_isLiving;
};

template<typename Entity>
class MeshComponent : public KT::Component<Entity>
{
public:
	MeshComponent(int nodeIndex, Ogre::Item* item) :m_item(item),m_nodeIndex(nodeIndex) {
		m_node = NodePpullSingleton().GetItem(nodeIndex);
	}
	~MeshComponent()
	{
		m_node->detachObject(m_item);
		NodePpullSingleton().ResetItem(m_nodeIndex);
	}
	Ogre::SceneNode* GetNode() const
	{
		return m_node;
	}
	Ogre::SceneNode* GetNode()
	{
		return m_node;
	}
	Ogre::Item* GetItem() const
	{
		return m_item;
	}
	Ogre::Item* GetItem()
	{
		return m_item;
	}
private:
	int m_nodeIndex;
	Ogre::SceneNode* m_node;
	Ogre::Item* m_item;
};