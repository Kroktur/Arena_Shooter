#pragma once
#include "Core/StateMachine.h"
#include "MyPlayer.h"

class PlayerStates : public KT::IState<MyPlayer>
{
public:
	PlayerStates(MyPlayer* entity);
	void OnEnter() override = 0; // Logic to execute when entering idle state
	void OnExit() override = 0; // Logic to execute when exiting idle state
	void ProcessInput() override = 0; // Process input for idle state
	void Update(const float& dt) override = 0; // Update logic for idle state
	void Render(const float& alpha) override = 0; // Render logic for idle state

protected:
	static bool isGoingForward();
	static bool isGoingBackward();
	static bool isGoingLeft();
	static bool isGoingRight();
	static bool isAttacking();
	static bool isDashing();
	static bool isJumping();
	static bool isRunning();
	void CommonTransitions();
};

class IdlePlayerState : public PlayerStates
{
public:
	IdlePlayerState(MyPlayer* entity);
	void OnEnter() override;
	void OnExit() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Render(const float& alpha) override;
};

class JumpPlayerState : public PlayerStates
{
public:
	JumpPlayerState(MyPlayer* entity);
	void OnEnter() override;
	void OnExit() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Render(const float& alpha) override;
};

class DashPlayerState : public PlayerStates
{
public:
	DashPlayerState(MyPlayer* entity);
	void OnEnter() override;
	void OnExit() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Render(const float& alpha) override;
private:
	float m_timer;
};

class AttackPlayerState : public PlayerStates
{
public:
	AttackPlayerState(MyPlayer* entity);
	void OnEnter() override;
	void OnExit() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Render(const float& alpha) override;
private:
	float m_cooldown;
};

class WalkPlayerState : public PlayerStates
{
public:
	WalkPlayerState(MyPlayer* entity);
	void OnEnter() override;
	void OnExit() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Render(const float& alpha) override;
};

class RunPlayerState : public PlayerStates
{
public:
	RunPlayerState(MyPlayer* entity);
	void OnEnter() override;
	void OnExit() override;
	void ProcessInput() override;
	void Update(const float& dt) override;
	void Render(const float& alpha) override;
};