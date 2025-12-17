#include "MyPlayer.h"

#include <iostream>

#include "OgreItem.h"
#include "OgreMesh2.h"
#include "OgreSubMesh2.h"
#include "OgreItem.h"
#include "OgreSceneNode.h"
#include "OgreHardwareVertexBuffer.h"
#include "OgreVector3.h"
#include "OgreMatrix4.h"
#include "Tools/Chrono.h"
#include "Vao/OgreAsyncTicket.h"
#include <OgreMesh.h>
#include <OgreSubMesh.h>
#include <OgreHardwareBuffer.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>

#include "MyMeshReader.h"
#include "OgreRoot.h"
#include "Math/MyMath.h"
#include "Math/Vector3.h"
#include <Animation/OgreSkeletonInstance.h>

std::vector<KT::Vector3F> extractVertexPositions(Ogre::Item* item)
{
    auto pos = MeshTools::GetAllPosition(item);
    return pos;
}

MyPlayer::~MyPlayer()
{
	//auto Ccrtp = static_cast<KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>*>(this);
	//auto root = Ccrtp->GetRoot();
	//if (!root)
	//	return;
	//auto manager = root->AsRoot()->GetSceneManager();
	//auto it = m_node->getAttachedObjectIterator();
	//ItemPull::Type::ResetObject(static_cast<Ogre::Item*>(it.getNext()), ItemPull::reset);
	//m_node->detachAllObjects();
	//NodePull::Type::ResetObject(m_node, NodePull::destroy, manager);
}

void MyPlayer::Init()
{
	m_stateMachine = std::make_unique < KT::StateMachine<MyPlayer>>(std::make_unique<IdlePlayerState>(this), 1);
	AddComponent<LivingComponent<IGameObject>>();
	auto Ccrtp = static_cast<KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>*>(this);
	auto root = Ccrtp->GetRoot();
	auto manager = root->AsRoot()->GetSceneManager();
	auto item = ItemPull::Type::PullValidObjectWithCondition(ItemPull::create, [](Ogre::Item* node) {return ItemPull::ConditionStr(node, "CubeFromMedia_d.mesh"); }, manager, "CubeFromMedia_d.mesh");
	auto mnode = NodePull::Type::PullValidObject(NodePull::create, manager);
	mnode.second->setPosition(-10, 0, 0);
	mnode.second->setScale(3, 3, 3);
	mnode.second->attachObject(item.second);
	Ogre::Item* it = item.second;
	Ogre::Node* n = mnode.second;

	AddComponent<MeshComponent<IGameObject>>(mnode.second,item.second);
	/*auto animation = AddComponent<AnimationComponent<IGameObject>>();
	animation->SetSkeleton(item.second, "Armature.skeleton");
	animation->AddAnimation("my_animation");
	animation->SetAnimation(0);
	animation->GetCurrentAnimation()->setEnabled(true);*/
	auto AABB = MeshTools::ExtractAABB(it);
	std::vector<KT::Vector3F> pts;
	pts.push_back(KT::Vector3F{ AABB.Amin.x, AABB.Amin.y, AABB.Amin.z });
	pts.push_back(KT::Vector3F{ AABB.Amax.x, AABB.Amin.y, AABB.Amin.z });
	pts.push_back(KT::Vector3F{ AABB.Amin.x, AABB.Amax.y, AABB.Amin.z });
	pts.push_back(KT::Vector3F{ AABB.Amin.x, AABB.Amin.y, AABB.Amax.z });
	pts.push_back(KT::Vector3F{ AABB.Amax.x, AABB.Amax.y, AABB.Amin.z });
	pts.push_back(KT::Vector3F{ AABB.Amin.x, AABB.Amax.y, AABB.Amax.z });
	pts.push_back(KT::Vector3F{ AABB.Amax.x, AABB.Amin.y, AABB.Amax.z });
	pts.push_back(KT::Vector3F{ AABB.Amax.x, AABB.Amax.y, AABB.Amax.z });
	auto obb = KT::OBB3DF(pts);
	auto collide = AddComponent<CollisionComponent<IGameObject>>();
	collide->AddObb(obb);
}

void MyPlayer::Exit()
{
	auto Ccrtp = static_cast<KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>*>(this);
	auto root = Ccrtp->GetRoot();
	auto manager = root->AsRoot()->GetSceneManager();
	auto mesh = GetComponent<MeshComponent<IGameObject>>();
	auto node = mesh->GetNode();
	auto it = node->getAttachedObjectIterator();
	ItemPull::Type::ResetObject(static_cast<Ogre::Item*>(it.getNext()), ItemPull::reset);
	node->detachAllObjects();
	NodePull::Type::ResetObject(node, NodePull::reset);
}

void MyPlayer::update(float deltaTime)
{
    //NE PAS TOUCHER
    m_stateMachine->ChangeState();
    m_stateMachine->Update(deltaTime);
    // FIN NE PAS TOUCHER
    moveTranslation(deltaTime);

  /* auto Animation = GetComponent<AnimationComponent<IGameObject>>()->GetCurrentAnimation();
	Animation->addTime(deltaTime);*/

	auto collide = GetComponent<CollisionComponent<IGameObject>>();
	auto node = GetComponent<MeshComponent<IGameObject>>()->GetNode();
	collide->UpdateGlobalOBB(0, fullTransform2Data(node->_getFullTransformUpdated()));

}
void MyPlayer::input()
{
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::A))
	{
		auto Ccrtp = static_cast<KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>*>(this);
		auto root = Ccrtp->GetRoot();
		root->AsRoot()->ToDoAtBegin([&]
		{
				auto* cast = static_cast<KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>*>(this);
				auto player = new MyPlayer2(cast,nullptr);
				player->Init();
		});
	}

	if (KT::Input::isPressed<KT::KEY>(KT::KEY::P))
	{
		GetComponent<LivingComponent<IGameObject>>()->EnableDeath();
	}



	//NE PAS TOUCHER
	m_stateMachine->ProcessInput();
	// FIN NE PAS TOUCHER

	inputPressed();
}

void MyPlayer::moveTranslation(float deltaTime)
{
	float x = 0;
	float z = 0;
	if (m_ZQSD[0])
		z = -10 * deltaTime;
	if (m_ZQSD[1])
		x = -10 * deltaTime;
	if (m_ZQSD[2])
		z = 10 * deltaTime;
	if (m_ZQSD[3])
		x = 10 * deltaTime;
	auto mesh = GetComponent<MeshComponent<IGameObject>>();
	mesh->GetNode()->translate(x, 0, z);
}

void MyPlayer::inputPressed()
{
	m_ZQSD[0] = false;
	m_ZQSD[1] = false;
	m_ZQSD[2] = false;
	m_ZQSD[3] = false;
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::Z))
		m_ZQSD[0] = true;
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::Q))
		m_ZQSD[1] = true;
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::S))
		m_ZQSD[2] = true;
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::D))
		m_ZQSD[3] = true;
}

void IdlePlayerState::Update(const float& dt)
{
	// Update logic for idle state

	//condition de changement vers jump validé
	SetNextState<JumpPlayerState>();

}
