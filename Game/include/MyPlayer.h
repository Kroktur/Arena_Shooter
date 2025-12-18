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
	MyPlayer(KT::IComposite<IGameObject,Demo::ArenaShooterGameState>* owner);
	~MyPlayer() override;
	void Init() override;
	void Exit() override;
	void update(float deltaTime) override;
	void input() override;
	// --- getters ---
	MyCamera* getCamera();

	// --- setters ---
	void SetCamera(MyCamera* camera);

	void startDashForward();
	void shootFireball();
	bool isGrounded() const;

	// --- movement ---
	void moveTranslation(float deltaTime);
	void inputPressed();
	bool isMoving() const;
	float m_runningSpeed;

private:
	bool m_ZQSD[4];
	std::unique_ptr<KT::StateMachine<MyPlayer>> m_stateMachine;
	Ogre::Vector3 m_velocity = Ogre::Vector3::ZERO;
	float m_dashSpeed = 1000;
	MyCamera* m_camera = nullptr;
	Ogre::Bone* m_fireBone = nullptr;

public:
	// movement variables
	float m_verticalVelocity = 0.0f;
	float m_jumpForce = 100.0f;
	float m_gravity = -100.0f;
	bool  m_isGrounded = true;
	float m_walkSpeed = 100;
	float m_runSpeed = 120.0f;
	float m_currentSpeed = 8.0f;
	float m_dashFriction = 80.0f;
};

inline MyPlayer::MyPlayer(KT::IComposite<IGameObject, Demo::ArenaShooterGameState>* owner) :
		KT::CompositeCRTP<MyPlayer, IGameObject, Demo::ArenaShooterGameState>(owner),
		m_stateMachine(nullptr)
{

}