//#include "Enemy.h"
//
//Enemy::Enemy(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner)
//    : KT::CompositeCRTP<Enemy, IGameObject, Demo::ArenaShooterGameState>(owner)
//{
//}
//
//void Enemy::Init()
//{
//	
//}
//
//void Enemy::Exit()
//{
//	
//}
//
//void Enemy::update(float dt)
//{
//	
//}
//
//void Enemy::SetTarget(MyPlayer* player)
//{
//	m_target = player;
//}
//
//void Enemy::GetTarget()
//{
//	return m_target;
//}
//
//bool Enemy::IsPlayerInRange(float range)
//{
//	auto node = GetComponent<MeshComponent<IGameObject>>()->GetNode();
//	auto playerNode = m_target->GetComponent<MeshComponent<IGameObject>>()->GetNode();
//
//	return node->getPosition().distance(playerNode->getPosition()) <= range;
//}
