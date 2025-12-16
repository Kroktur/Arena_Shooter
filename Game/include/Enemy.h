//#pragma once
//#include "ASGameState.h"
//#include "IGameObject.h"
//#include "Core/CompositeCrtp.h"
//#include "Core/StateMachine.h"
//#include "GameComponent.h"
//
//class Enemy : public IGameObject, public KT::CompositeCRTP<Enemy, IGameObject, Demo::ArenaShooterGameState>
//{
//public:
//    Enemy(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner);
//    ~Enemy() override {}
//
//    void Init() override;
//    void Exit() override;
//    void update(float dt) override;
//    void input() override {}
//
//    void SetTarget(MyPlayer* player);
//    void GetTarget();
//
//    bool IsPlayerInRange(float range);
//    void MoveTowardPlayer(float dt);
//    virtual void AttackPlayer();
//
//protected:
//    std::unique_ptr<KT::StateMachine<Enemy>> m_stateMachine;
//    MyPlayer* m_target = nullptr;
//
//public:
//    float m_speed = 10.0f;
//    float m_detectionRange = 25.0f;
//    float m_attackRange = 2.0f;
//    float m_attackCooldown = 1.0f;
//};