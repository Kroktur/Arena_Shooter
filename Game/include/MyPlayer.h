#pragma once
#include "ASGameState.h"
#include "GameComponent.h"
#include "IGameObject.h"
#include "Core/CompositeCrtp.h"
#include "Core/Input.h"
#include "Core/StateMachine.h"
#include "Spells.h"

class MyPlayer : public IGameObject, public KT::CompositeCRTP<MyPlayer,IGameObject,Demo::ArenaShooterGameState>
{
public:
	MyPlayer(IComposite<IGameObject,Demo::ArenaShooterGameState>* owner);
	~MyPlayer() override;
	void Init() override;
	void Exit() override;
	void update(float deltaTime) override;
	void input() override;
	// --- getters ---
	MyCamera* getCamera();
//	float getHealth() const;
//	float getRunningSpeed() const;
//	float getMana() const;
//	float getMaxHealth() const;

	// --- setters ---
	void SetCamera(MyCamera* camera);
//	void setHealth(float health);
//	void setRunningSpeed(float speed);
//	void setMana(float mana);
//
//	// --- actions ---
//	void takeDamage(float damage);
//	void recoverMana(float amount);
//	void consumeMana(float amount);
	void startDashForward();
	void shootFireball();
	bool isGrounded() const;

	// --- movement ---
	void moveTranslation(float deltaTime);
	void inputPressed();
	bool isMoving() const;
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
	Ogre::Vector3 m_velocity = Ogre::Vector3::ZERO;
	float m_dashSpeed = 50.0f;
	MyCamera* m_camera = nullptr;
	std::vector<std::unique_ptr<Fireball>> m_projectiles;
public:
	// movement variables
	float m_verticalVelocity = 0.0f;
	float m_jumpForce = 20.0f;
	float m_gravity = -45.0f;
	bool  m_isGrounded = true;
	float m_walkSpeed = 15.0f;
	float m_runSpeed = 35.0f;
	float m_currentSpeed = 8.0f;
	float m_dashFriction = 80.0f;
};

inline MyPlayer::MyPlayer(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner) :
		KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>(owner),
		m_stateMachine(nullptr)
{

}