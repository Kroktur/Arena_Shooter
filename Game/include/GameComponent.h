#pragma once
#include "Core/Component.h"
#include "ItemPull.h"
#include <Animation/OgreSkeletonInstance.h>

#include "MyTransform.h"
#include "Math/OBB.h"

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
	MeshComponent(Ogre::SceneNode* node,Ogre::Item* item) :KT::Component<Entity>(),m_item(item),m_node(node) {
		
	}
	~MeshComponent()
	{

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
	void Detach()
	{
		m_node->detachObject(m_item);
	}
private:
	Ogre::SceneNode* m_node;
	Ogre::Item* m_item;
};

template<typename Entity>
class AnimationComponent : public KT::Component<Entity>
{
public:
	AnimationComponent() = default;
	void SetSkeleton(Ogre::Item* item,const std::string& skeletonFile)
	{
		if (!item)
			throw std::runtime_error("item invalid");
		m_skeletonInstance = item->getSkeletonInstance();
		m_skeletonInstance->addAnimationsFromSkeleton(skeletonFile, Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME);
	}
	void SetAnimation(size_t index)
	{
		if (index >= m_animations.size())
			throw std::out_of_range("index not in range");
		if (!m_skeletonInstance->hasAnimation(m_animations[index]))
			throw std::out_of_range("animation not register");
		m_currentAnimation = m_skeletonInstance->getAnimation(m_animations[index]);
	}

	void SetAnimation(const std::string& str)
	{
		for (int i = 0 ;i < m_animations.size() ;++i )
		{
			if (m_animations[i] == str)
			{
				SetAnimation(i);
				return;
			}
		}
		throw std::out_of_range("animation not register");
	}

	void AddAnimation(const std::string& str)
	{
		if (!m_skeletonInstance)
			throw std::runtime_error("skeleton not set");
		m_animations.push_back(str);
	}
	Ogre::SkeletonAnimation* GetCurrentAnimation() const 
	{
		return m_currentAnimation;	
	}
	Ogre::SkeletonInstance* GetCurrentSkeleton() const 
	{
		return m_skeletonInstance;
	}
	std::vector<std::string> GetAnimationStr()
	{
		return m_animations;
	}
	~AnimationComponent() = default;
private:
	std::vector<std::string> m_animations;
	Ogre::SkeletonAnimation* m_currentAnimation;
	Ogre::SkeletonInstance* m_skeletonInstance;
};

template<typename Entity>
class CollisionComponent : public KT::Component<Entity>
{
public:
	CollisionComponent() = default;
	~CollisionComponent() = default;
	void AddObb(const KT::OBB3DF& obb)
	{
		m_localObbs.push_back(obb);
		m_globalObbs.push_back(obb);
	}
	void RemoveObb(int index)
	{
		if (index >= m_localObbs.size())
			throw std::out_of_range("index not found");

		int currentIndex = 0;
		auto it2 = m_localObbs.begin();
		for (auto it = m_globalObbs.begin() ; it != m_globalObbs.end(); ++it,++it2,++currentIndex)
		{
			if (currentIndex == index)
				{
				m_globalObbs.erase(it);
				m_localObbs.erase(it2);
				return;
			}
		}
	}
	const std::vector<KT::OBB3DF>& GetLocalObbs() const
	{
		return m_localObbs;
	}
	const std::vector<KT::OBB3DF>& GetGlobalObbs() const
	{
		return m_globalObbs;
	}
	void UpdateGlobalOBB(int index, TransformOBBData data)
	{
		if (index >= m_localObbs.size())
			throw std::out_of_range("index not found");
		m_globalObbs[index] = TransformOBB::ApplyTransform(m_localObbs[index],data);
	}

private:
	std::vector<KT::OBB3DF> m_localObbs;
	std::vector< KT::OBB3DF> m_globalObbs;
};