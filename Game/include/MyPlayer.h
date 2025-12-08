#pragma once
#include "ASGameState.h"
#include "IGameObject.h"
#include "Core/CompositeCrtp.h"
#include "Core/Input.h"
#include "Core/StateMachine.h"

class MyPlayer : public IGameObject, public compositeGO<MyPlayer>
{
public:
	MyPlayer(IComposite<IGameObject,Demo::ArenaShooterGameState>* owner,Ogre::SceneNode* node);
	~MyPlayer() override= default;
	void Init() override;
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

	std::unique_ptr<KT::StateMachine<MyPlayer>> m_stateMachine;
};

inline MyPlayer::MyPlayer(IComposite<IGameObject, Demo::ArenaShooterGameState>* owner, Ogre::SceneNode* node) : compositeGO<MyPlayer>(owner),m_stateMachine(nullptr)
{
	m_node = node;
}