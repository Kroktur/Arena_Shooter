#include "MyPlayer.h"

void MyPlayer::Init()
{
	m_stateMachine = std::make_unique < KT::StateMachine<MyPlayer>>(std::make_unique<IdlePlayerState>(this), 1);
}

void MyPlayer::update(float deltaTime)
{
	//NE PAS TOUCHER
	m_stateMachine->ChangeState();
	m_stateMachine->Update(deltaTime);
	// FIN NE PAS TOUCHER
	moveTranslation(deltaTime);
}
void MyPlayer::input()
{
	//NE PAS TOUCHER
	m_stateMachine->ProcessInput();
	// FIN NE PAS TOUCHER

	inputPressed();
}

void MyPlayer::moveTranslation(float deltaTime) const
{
	float x = 0;
	float z = 0;
	if (m_ZQSD[0])
		z = -10 * deltaTime;
	if (m_ZQSD[1])
		x = -10 * deltaTime;
	if (m_ZQSD[2])
		z = 10 * deltaTime;
	if (m_ZQSD[3])
		x = 10 * deltaTime;
	m_node->translate(x, 0, z);
}

void MyPlayer::inputPressed()
{
	m_ZQSD[0] = false;
	m_ZQSD[1] = false;
	m_ZQSD[2] = false;
	m_ZQSD[3] = false;
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::Z))
		m_ZQSD[0] = true;
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::Q))
		m_ZQSD[1] = true;
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::S))
		m_ZQSD[2] = true;
	if (KT::Input::isPressed<KT::KEY>(KT::KEY::D))
		m_ZQSD[3] = true;
}

void IdlePlayerState::Update(const float& dt)
{
	// Update logic for idle state

	//condition de changement vers jump validé
	SetNextState<JumpPlayerState>();
}
