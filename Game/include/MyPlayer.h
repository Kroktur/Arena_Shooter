#pragma once
#include "ASGameState.h"
#include "GameComponent.h"
#include "IGameObject.h"
#include "Core/CompositeCrtp.h"
#include "Core/Input.h"
#include "Core/StateMachine.h"

class MyPlayer : public IGameObject, public KT::CompositeCRTP<MyPlayer,IGameObject,Demo::ArenaShooterGameState>
{
public:
	MyPlayer(IComposite<IGameObject,Demo::ArenaShooterGameState>* owner);
	~MyPlayer() override;
	void Init() override;
	void Exit() override;
	void update(float deltaTime) override;
	void input() override;
//	// --- getters ---
//	float getHealth() const;
//	float getRunningSpeed() const;
//	float getMana() const;
//	float getMaxHealth() const;
//
//	// --- setters ---
//	void setHealth(float health);
//	void setRunningSpeed(float speed);
//	void setMana(float mana);
//
//	// --- actions ---
//	void takeDamage(float damage);
//	void recoverMana(float amount);
//	void consumeMana(float amount);

	// --- movement ---
	void moveTranslation(float deltaTime);
	void inputPressed();
//private:
//	float m_health;
//	float m_mana;
	float m_runningSpeed;
//	float m_shootCadence;
//	const float m_maxHealth = 100.0f;
//	const float m_maxMana = 100.0f;
private:
	bool m_ZQSD[4];
	std::unique_ptr<KT::StateMachine<MyPlayer>> m_stateMachine;
};

<<<<<<< HEAD
inline MyPlayer::MyPlayer(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner, Ogre::SceneNode* node) : compositeGO<MyPlayer>(owner),m_stateMachine(nullptr)
=======
class IdlePlayerState : public KT::IState<MyPlayer>
{
	public:
	IdlePlayerState(MyPlayer* entity) :KT::IState<MyPlayer>(entity) {}
	void OnEnter() override
	{
		// Logic to execute when entering idle state
	}
	void OnExit() override
	{
		// Logic to execute when exiting idle state
	}
	void ProcessInput() override
	{
		// Process input for idle state
	}
	void Update(const float& dt) override;

	void Render(const float& alpha) override
	{
		// Render logic for idle state
	}
};

class JumpPlayerState : public KT::IState<MyPlayer>
{
public:
	JumpPlayerState(MyPlayer* entity) :KT::IState<MyPlayer>(entity) {}
	void OnEnter() override
	{
		// Logic to execute when entering idle state
	}
	void OnExit() override
	{
		// Logic to execute when exiting idle state
	}
	void ProcessInput() override
	{
		// Process input for idle state
	}
	void Update(const float& dt) override
	{
		// Update logic for idle state
	}
	void Render(const float& alpha) override
	{
		// Render logic for idle state
	}
};



inline MyPlayer::MyPlayer(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner) : KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>(owner),m_stateMachine(nullptr)
>>>>>>> origin/main
{

}

class MyPlayer2 : public IGameObject, public KT::CompositeCRTP<MyPlayer2, IGameObject, Demo::ArenaShooterGameState>
{
public:
	MyPlayer2(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner, Ogre::SceneNode* node) : KT::CompositeCRTP<MyPlayer2, IGameObject, Demo::ArenaShooterGameState>(owner)
	{
		m_node = node;
	}
	void Init() override
	{
		
	}
	 void Exit() override
	{
		
	}
	void update(float deltaTime) override
	{
		int toto = 0;
	}
	void input() override
	{
		
	}
	//	// --- getters ---
	//	float getHealth() const;
	//	float getRunningSpeed() const;
	//	float getMana() const;
	//	float getMaxHealth() const;
	//
	//	// --- setters ---
	//	void setHealth(float health);a
	//	void setRunningSpeed(float speed);
	//	void setMana(float mana);
	//
	//	// --- actions ---
	//	void takeDamage(float damage);
	//	void recoverMana(float amount);
	//	void consumeMana(float amount);

		// --- movement ---
	void moveTranslation(float deltaTime) const;
	void inputPressed();
	//private:
	//	float m_health;
	//	float m_mana;
	float m_runningSpeed;
	//	float m_shootCadence;
	//	const float m_maxHealth = 100.0f;
	//	const float m_maxMana = 100.0f;
private:
	bool m_ZQSD[4];
	Ogre::SceneNode* m_node;
};