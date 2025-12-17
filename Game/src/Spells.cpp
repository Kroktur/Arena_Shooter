//#include "Spells.h"
//#include <OgreItem.h>
//#include "GameComponent.h"
//
//
//
//
//void Fireball::Init()
//{
//	/*AddComponent<LivingComponent<IGameObject>>();
//	auto Ccrtp = static_cast<KT::CompositeCRTP<Fireball, IGameObject, Demo::ArenaShooterGameState>*>(this);
//	auto root = Ccrtp->GetRoot();
//	auto manager = root->AsRoot()->GetSceneManager();
//	auto item = ItemPull::Type::PullValidObjectWithCondition(ItemPull::create, [](Ogre::Item* node) {return ItemPull::ConditionStr(node, "CubeFromMedia_d.mesh"); }, manager, "CubeFromMedia_d.mesh");
//	auto mnode = NodePull::Type::PullValidObject(NodePull::create, manager);
//	mnode.second->setPosition(m_pos);
//	mnode.second->setScale(1, 1, 1);
//	mnode.second->attachObject(item.second);
//	auto mesh = AddComponent<MeshComponent<IGameObject>>(mnode.second, item.second);*/
//}
//
//
//void Fireball::update(float dt)
//{
//	/*auto mesh = GetComponent<MeshComponent<IGameObject>>();
//	auto m_node = mesh->GetNode();
//
//    m_node->translate(m_direction * m_speed * dt, Ogre::Node::TS_WORLD);
//    m_node->yaw(Ogre::Degree(360 * dt));*/
//}
//
//void Fireball::Exit()
//{
//	//auto Ccrtp = static_cast<KT::CompositeCRTP<Fireball, IGameObject, Demo::ArenaShooterGameState>*>(this);
//	//auto root = Ccrtp->GetRoot();
//	//auto manager = root->AsRoot()->GetSceneManager();
//	//auto mesh = GetComponent<MeshComponent<IGameObject>>();
//	//auto node = mesh->GetNode();
//	//auto it = node->getAttachedObjectIterator();
//	//ItemPull::Type::ResetObject(static_cast<Ogre::Item*>(it.getNext()), ItemPull::reset);
//	//node->detachAllObjects();
//	//NodePull::Type::ResetObject(node, NodePull::destroy, manager);
//}
//
