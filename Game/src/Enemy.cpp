//#include "Enemy.h"
//#include "EnemyStates.h"
//
//Enemy::Enemy(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner)
//    : KT::CompositeCRTP<Enemy, IGameObject, Demo::ArenaShooterGameState>(owner)
//{
//}
//
//void Enemy::Init()
//{
//	m_stateMachine = std::make_unique<KT::StateMachine<Enemy>>(std::make_unique<IdleEnemyState>(this), 1);
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
//MyPlayer* Enemy::GetTarget() const
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
//
//void Enemy::MoveTowardPlayer(float dt)
//{
//	if (!m_target)
//		return;
//	auto node = GetComponent<MeshComponent<IGameObject>>()->GetNode();
//	auto playerNode = m_target->GetComponent<MeshComponent<IGameObject>>()->GetNode();
//	Ogre::Vector3 direction = playerNode->getPosition() - node->getPosition();
//	direction.z = 0;
//	direction.normalise();
//	node->translate(direction * m_speed * dt, Ogre::Node::TS_WORLD);
//}
//
//void Enemy::AttackPlayer()
//{
//	
//}
//
//RacoonEnemy::RacoonEnemy(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner)
//	: Enemy(owner)
//{
//}
//
//void RacoonEnemy::Init()
//{
//	Enemy::Init();
//}
//void RacoonEnemy::Exit()
//{
//	Enemy::Exit();
//}
//
//void RacoonEnemy::update(float dt)
//{
//	Enemy::update(dt);
//}
//
//void RacoonEnemy::AttackPlayer()
//{
//
//}
//
//OwlEnemy::OwlEnemy(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner)
//	: Enemy(owner)
//{
//}
//
//void OwlEnemy::Init()
//{
//	Enemy::Init();
//}
//
//void OwlEnemy::Exit()
//{
//	Enemy::Exit();
//}
//
//void OwlEnemy::update(float dt)
//{
//	Enemy::update(dt);
//}
//
//void OwlEnemy::AttackPlayer()
//{
//	
//}
//
//FoxBossEnemy::FoxBossEnemy(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner)
//	: Enemy(owner)
//{
//}
//
//void FoxBossEnemy::Init()
//{
//	Enemy::Init();
//}
//
//void FoxBossEnemy::Exit()
//{
//	Enemy::Exit();
//}
//
//void FoxBossEnemy::update(float dt)
//{
//	Enemy::update(dt);
//}
//
//void FoxBossEnemy::AttackPlayer()
//{
//	
//}