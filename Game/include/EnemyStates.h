//#pragma once
//#include "Core/StateMachine.h"
//#include "Enemy.h"
//
//class EnemyStates : public KT::IState<Enemy>
//{
//public:
//	EnemyStates(Enemy* entity);
//	void OnEnter() override = 0; // Logic to execute when entering idle state
//	void OnExit() override = 0; // Logic to execute when exiting idle state
//	void ProcessInput() override = 0; // Process input for idle state
//	void Update(const float& dt) override = 0; // Update logic for idle state
//	void Render(const float& alpha) override = 0; // Render logic for idle state
//};
//
//class IdleEnemyState : public EnemyStates
//{
//	public:
//	IdleEnemyState(Enemy* entity);
//	void OnEnter() override;
//	void OnExit() override;
//	void ProcessInput() override;
//	void Update(const float& dt) override;
//	void Render(const float& alpha) override;
//};
//
//class ChaseEnemyState : public EnemyStates
//{
//	public:
//	ChaseEnemyState(Enemy* entity);
//	void OnEnter() override;
//	void OnExit() override;
//	void ProcessInput() override;
//	void Update(const float& dt) override;
//	void Render(const float& alpha) override;
//};
//
//class AttackEnemyState : public EnemyStates
//{
//public:
//	AttackEnemyState(Enemy* entity);
//	void OnEnter() override;
//	void OnExit() override;
//	void ProcessInput() override;
//	void Update(const float& dt) override;
//	void Render(const float& alpha) override;
//};
//
//class DeadEnemyState : public EnemyStates
//{
//	public:
//	DeadEnemyState(Enemy* entity);
//	void OnEnter() override;
//	void OnExit() override;
//	void ProcessInput() override;
//	void Update(const float& dt) override;
//	void Render(const float& alpha) override;
//};