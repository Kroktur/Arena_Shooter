#pragma once
#include "IGameObject.h"
#include "OgreSceneManager.h"
#include "Core/CompositeCrtp.h"
#include "ASGameState.h"
#include "ASGameState.h"
#include "GameComponent.h"
#include "IGameObject.h"
#include "Core/CompositeCrtp.h"
#include "Core/Input.h"
#include "Core/StateMachine.h"
class Fireball : public IGameObject, public KT::CompositeCRTP<Fireball, IGameObject, Demo::ArenaShooterGameState>
{
public:
	Fireball(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner, const Ogre::Vector3& pos, const Ogre::Vector3& dir) : KT::CompositeCRTP<Fireball, IGameObject, Demo::ArenaShooterGameState>(owner), m_direction(dir), m_pos(pos),m_speed(200.0f) {}
    ~Fireball() override = default;
    void Init() override
    {
        	AddComponent<LivingComponent<IGameObject>>();
	auto Ccrtp = static_cast<KT::CompositeCRTP<Fireball, IGameObject, Demo::ArenaShooterGameState>*>(this);
	auto root = Ccrtp->GetRoot();
	auto manager = root->AsRoot()->GetSceneManager();
	auto item = ItemPull::Type::PullValidObjectWithCondition(ItemPull::create, [](Ogre::Item* node) {return ItemPull::ConditionStr(node, "CubeFromMedia_d.mesh"); }, manager, "CubeFromMedia_d.mesh");
	auto mnode = NodePull::Type::PullValidObject(NodePull::create, manager);
	mnode.second->setPosition(m_pos);
	mnode.second->setScale(1, 1, 1);
	mnode.second->attachObject(item.second);
	auto mesh = AddComponent<MeshComponent<IGameObject>>(mnode.second, item.second);

    }
    void update(float dt) override
    {
        auto mesh = GetComponent<MeshComponent<IGameObject>>();
		auto m_node = mesh->GetNode();

		 m_node->translate(m_direction * m_speed * dt, Ogre::Node::TS_WORLD);
		m_node->yaw(Ogre::Degree(360 * dt));

    }
   void Exit() override
    {
       	auto Ccrtp = static_cast<KT::CompositeCRTP<Fireball, IGameObject, Demo::ArenaShooterGameState>*>(this);
	auto root = Ccrtp->GetRoot();
	auto manager = root->AsRoot()->GetSceneManager();
	auto mesh = GetComponent<MeshComponent<IGameObject>>();
	auto node = mesh->GetNode();
	auto it = node->getAttachedObjectIterator();
	ItemPull::Type::ResetObject(static_cast<Ogre::Item*>(it.getNext()), ItemPull::reset);
	node->detachAllObjects();
	NodePull::Type::ResetObject(node, NodePull::destroy, manager);
    }
    void input() override{}

private:

    Ogre::Vector3 m_pos;
    Ogre::Vector3 m_direction;
    float m_speed;
    float m_lifetime;
};
