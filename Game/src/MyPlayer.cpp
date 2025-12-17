#include "MyPlayer.h"
#include "OgreItem.h"
#include "OgreSceneNode.h"
#include "OgreVector3.h"
#include "Tools/Chrono.h"
#include <OgreMesh.h>
#include "MyMeshReader.h"
#include "Math/Vector3.h"
#include "PlayerStates.h"
#include "NodePull.h"
#include "ItemPull.h"
#include <Animation/OgreBone.h>
//#include "Spells.h"

#include <Animation/OgreSkeletonInstance.h>

#include "Spells.h"

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
	auto item = ItemPull::Type::PullValidObjectWithCondition(ItemPull::create, [](Ogre::Item* node) {return ItemPull::ConditionStr(node, "HandPlane.mesh"); }, manager, "HandPlane.mesh");
	auto mnode = NodePull::Type::PullValidObject(NodePull::create, manager);
	mnode.second->setPosition(0, 10, 0);
	mnode.second->setScale(1, 1, 1);
	mnode.second->yaw(Ogre::Degree(180));
	mnode.second->attachObject(item.second);
	auto mesh = AddComponent<MeshComponent<IGameObject>>(mnode.second,item.second);
	
	/*auto m_skeletonInstance = item.second->getSkeletonInstance();
	m_skeletonInstance->addAnimationsFromSkeleton("HandArmature.skeleton", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME);
	m_skeletonInstance->setParentNode(mnode.second);
	m_fireBone = m_skeletonInstance->getBone("forearm.001.R");*/


	auto animation = AddComponent<AnimationComponent<IGameObject>>();
	animation->SetSkeleton(item.second, "HandArmature.skeleton");
	animation->AddAnimation("attack_base");
	animation->SetAnimation(0);
	animation->GetCurrentAnimation()->setEnabled(true);


	auto AABB = MeshTools::ExtractAABB(item.second);
	auto obb = KT::OBB3DF(AABB.GetPts());
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

	auto item = GetComponent<MeshComponent<IGameObject>>()->GetItem();
	static KT::Chrono<float> test;

    auto Animation = GetComponent<AnimationComponent<IGameObject>>()->GetCurrentAnimation();
	Animation->addTime(deltaTime / 4);

	auto node = GetComponent<MeshComponent<IGameObject>>()->GetNode();
	auto pos = node->getPosition();
	node->setOrientation(m_camera->getCamera()->getOrientation());

	// update world box position
	auto collide = GetComponent<CollisionComponent<IGameObject>>();
	collide->UpdateGlobalOBB(0, fullTransform2Data(node->_getFullTransformUpdated()));
	// Update projectiles


	// Dashing movement
	if (!m_velocity.isZeroLength())
	{
		auto node = GetComponent<MeshComponent<IGameObject>>()->GetNode();

		node->translate(m_velocity * deltaTime, Ogre::Node::TS_WORLD);

		float speed = m_velocity.length();
		speed -= m_dashFriction * deltaTime;

		if (speed <= 0.0f)
			m_velocity = Ogre::Vector3::ZERO;
		else
			m_velocity = m_velocity.normalisedCopy() * speed;
	}

	// Gravity and jumping
	if (!m_isGrounded)
		m_verticalVelocity += m_gravity * deltaTime;

	Ogre::Vector3 pos2 = node->getPosition();
	pos.y += m_verticalVelocity * deltaTime;

	if (pos.y <= 0.0f)
	{
		pos.y = 0.0f;
		m_verticalVelocity = 0.0f;
		m_isGrounded = true;
	}

	node->setPosition(pos);

    if (test.GetElapsedTime().AsSeconds() > 5)
    {
       //extractVertexPositions(item);
    }

	

}

void MyPlayer::input()
{
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::A))
	{
		/*auto Ccrtp = static_cast<KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>*>(this);
		auto root = Ccrtp->GetRoot();
		root->AsRoot()->ToDoAtBegin([&]
		{
				auto* cast = static_cast<KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>*>(this);
				auto player = new MyPlayer2(cast,nullptr);
				player->Init();
		});*/
	}

	if (KT::Input::isPressed<KT::KEY>(KT::KEY::P))
	{
		GetComponent<LivingComponent<IGameObject>>()->EnableDeath();
	}
	/*std::cout << this->GetChild().size() << " \n";*/

	//NE PAS TOUCHER
	m_stateMachine->ProcessInput();
	// FIN NE PAS TOUCHER

	inputPressed();
}

void MyPlayer::moveTranslation(float deltaTime)
{
	Ogre::Vector3 move = Ogre::Vector3::ZERO;

	if (KT::Input::isPressed<KT::KEY>(KT::KEY::Z))
		move += m_camera->getCamera()->getDirection();
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::S))
		move -= m_camera->getCamera()->getDirection();
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::Q))
		move -= m_camera->getCamera()->getRight();
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::D))
		move += m_camera->getCamera()->getRight();

	move.y = 0;
	if (!move.isZeroLength())
		move.normalise();

	auto node = GetComponent<MeshComponent<IGameObject>>()->GetNode();
	node->translate(move * m_currentSpeed * deltaTime, Ogre::Node::TS_WORLD);
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

void MyPlayer::SetCamera(MyCamera* camera)
{
	m_camera = camera;
}

void MyPlayer::startDashForward()
{
	Ogre::Vector3 forward = m_camera->getCamera()->getDirection();
	forward.y = 0;
	forward.normalise();

	m_velocity = forward * m_dashSpeed;
}

void MyPlayer::shootFireball()
{
	auto mesh = GetComponent<MeshComponent<IGameObject>>();
	auto node = mesh->GetNode();

	Ogre::Vector3 position = node->getPosition();
	Ogre::Vector3 forward = m_camera->getCamera()->getDirection().normalisedCopy();
	Ogre::Vector3 right = m_camera->getCamera()->getRight().normalisedCopy();
	Ogre::Vector3 up = m_camera->getCamera()->getUp().normalisedCopy();

	Ogre::Vector3 offset = forward * 6.0f + right * 2.8f + up * 2.3f;

	Ogre::Vector3 firePos = position + offset;
	auto Ccrtp = static_cast<KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>*>(this);
	auto root = Ccrtp->GetRoot();
	auto manager = root->AsRoot()->GetSceneManager();
	//m_projectiles.push_back(std::make_unique<Fireball>(manager, firePos, forward));

	auto fire = new Fireball(this, firePos, forward);
	fire->Init();

	/*auto mesh = GetComponent<MeshComponent<IGameObject>>();
	auto item = mesh->GetItem();
	auto skeleton = item->getSkeletonInstance();

	if (!skeleton || !m_fireBone)
		return;

	item->_updateAnimation();

	const Ogre::SimpleMatrixAf4x3& packedMat = m_fireBone->_getFullTransform();

	Ogre::Matrix4 boneMat;
	packedMat.store4x3(&boneMat);

	Ogre::Matrix4 worldMat = mesh->GetNode()->_getFullTransform() * boneMat;


	Ogre::Vector3 firePos = worldMat.getTrans();


	Ogre::Matrix3 rot3x3;
	worldMat.extract3x3Matrix(rot3x3);

	Ogre::Quaternion fireRot(rot3x3);

	Ogre::Vector3 forward = fireRot * Ogre::Vector3::NEGATIVE_UNIT_Z;
	forward.normalise();

	auto Ccrtp = static_cast<KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>*>(this);
	auto root = Ccrtp->GetRoot();
	auto manager = root->AsRoot()->GetSceneManager();

	m_projectiles.push_back(std::make_unique<Fireball>(manager, firePos, forward));*/
}


bool MyPlayer::isGrounded() const
{
	return m_isGrounded;
}

bool MyPlayer::isMoving() const
{
	return KT::Input::isPressed<KT::KEY>(KT::KEY::Z) ||
		KT::Input::isPressed<KT::KEY>(KT::KEY::S) ||
		KT::Input::isPressed<KT::KEY>(KT::KEY::Q) ||
		KT::Input::isPressed<KT::KEY>(KT::KEY::D);
}

MyCamera* MyPlayer::getCamera()
{
	return m_camera;
}