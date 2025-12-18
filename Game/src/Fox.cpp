#include "Fox.h"

#include "MyMeshReader.h"

Fox::Fox(KT::IComposite<IGameObject, Demo::ArenaShooterGameState>* owner) : KT::CompositeCRTP<Fox, IGameObject, Demo::ArenaShooterGameState>(owner)
{
}

void Fox::Init()
{
	AddComponent<LivingComponent<IGameObject>>();
	auto Ccrtp = static_cast<KT::CompositeCRTP<Fox, IGameObject, Demo::ArenaShooterGameState>*>(this);
	auto root = Ccrtp->GetRoot();
	auto manager = root->AsRoot()->GetSceneManager();
	auto item = ItemPull::Type::PullValidObjectWithCondition(ItemPull::create, [](Ogre::Item* node) {return ItemPull::ConditionStr(node, "RenardPlane.001.mesh"); }, manager, "RenardPlane.001.mesh");
	auto mnode = NodePull::Type::PullValidObject(NodePull::create, manager);
	mnode.second->setPosition(0, -10, 0);
	mnode.second->setScale(5, 5, 5);
	mnode.second->attachObject(item.second);
	AddComponent<MeshComponent<IGameObject>>(mnode.second, item.second);
	auto AABB = MeshTools::ExtractAABB(item.second);
	auto obb = KT::OBB3DF(AABB.GetPts());
	auto collide = AddComponent<CollisionComponent<IGameObject>>();
	collide->AddObb(obb);
}

void Fox::Exit()
{
	auto Ccrtp = static_cast<KT::CompositeCRTP<Fox, IGameObject, Demo::ArenaShooterGameState>*>(this);
	auto root = Ccrtp->GetRoot();
	auto manager = root->AsRoot()->GetSceneManager();
	auto mesh = GetComponent<MeshComponent<IGameObject>>();
	auto node = mesh->GetNode();
	auto it = node->getAttachedObjectIterator();
	ItemPull::Type::ResetObject(static_cast<Ogre::Item*>(it.getNext()), ItemPull::reset);
	node->detachAllObjects();
	NodePull::Type::ResetObject(node, NodePull::reset);
}

void Fox::update(float deltaTime)
{
	auto collide = GetComponent<CollisionComponent<IGameObject>>();
	auto node = GetComponent<MeshComponent<IGameObject>>()->GetNode();
	collide->UpdateGlobalOBB(0, fullTransform2Data(node->_getFullTransformUpdated()));
}
