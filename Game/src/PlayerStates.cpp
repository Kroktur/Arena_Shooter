#include "PlayerStates.h"
#include "Core/Input.h"

PlayerStates::PlayerStates(MyPlayer* entity) : KT::IState<MyPlayer>(entity)
{}

bool PlayerStates::isGoingForward()
{
	return KT::Input::isPressed<KT::KEY>(KT::KEY::Z);
}

bool PlayerStates::isGoingBackward()
{
    return KT::Input::isPressed<KT::KEY>(KT::KEY::S);
}

bool PlayerStates::isGoingLeft()
{
    return KT::Input::isPressed<KT::KEY>(KT::KEY::Q);
}

bool PlayerStates::isGoingRight()
{
    return KT::Input::isPressed<KT::KEY>(KT::KEY::D);
}

bool PlayerStates::isAttacking()
{
    return KT::Input::isPressed<KT::MOUSE>(KT::MOUSE::LHS);
}

bool PlayerStates::isJumping()
{
    return KT::Input::isPressed<KT::KEY>(KT::KEY::SPACE);
}

bool PlayerStates::isDashing()
{
    return KT::Input::isPressed<KT::KEY>(KT::KEY::LSHIFT);
}

void PlayerStates::CommonTransitions()
{
    if (isJumping())
    {
        SetNextState<JumpPlayerState>();
        return;
    }

    if (isAttacking())
    {
        SetNextState<AttackPlayerState>();
        return;
    }

    if (isDashing() && isGoingForward())
    {
        SetNextState<DashPlayerState>();
        return;
    }
}


//--------------------------------------
//--- IdlePlayerState Implementation ---
//--------------------------------------

IdlePlayerState::IdlePlayerState(MyPlayer* entity) : PlayerStates(entity)
{
    /*m_entity->GetComponent<MeshComponent<IGameObject>>()->GetNode();*/
}

void IdlePlayerState::OnEnter()
{
	// Idle anim
}

void IdlePlayerState::OnExit()
{
	// end idle anim
}

void IdlePlayerState::ProcessInput()
{

}

void IdlePlayerState::Update(const float& dt)
{
    CommonTransitions();

    if (isGoingForward() || isGoingBackward() || isGoingLeft() || isGoingRight())
    {
        SetNextState<RunPlayerState>();
        return;
    }
}

void IdlePlayerState::Render(const float& alpha)
{
	// Render logic for idle state
}

//--------------------------------------
//--- JumpPlayerState Implementation ---
//--------------------------------------

JumpPlayerState::JumpPlayerState(MyPlayer* entity) : PlayerStates(entity)
{
}

void JumpPlayerState::OnEnter()
{
	// Logic to execute when entering jump state
}

void JumpPlayerState::OnExit()
{
	// Logic to execute when exiting jump state
}

void JumpPlayerState::ProcessInput()
{
}

void JumpPlayerState::Update(const float& dt)
{
	// Update logic for jump state

    if (m_entity->isGrounded())
    {
        if (m_entity->isMoving())
            SetNextState<RunPlayerState>();
        else
            SetNextState<IdlePlayerState>();
    }
}

void JumpPlayerState::Render(const float& alpha)
{
	// Render logic for jump state
}

//--------------------------------------
//--- DashPlayerState Implementation ---
//--------------------------------------

DashPlayerState::DashPlayerState(MyPlayer* entity) : PlayerStates(entity)
{
}

void DashPlayerState::OnEnter()
{
	// Logic to execute when entering dash state
    m_timer = 0.15f;
    m_entity->startDashForward();
}

void DashPlayerState::OnExit()
{
	// Logic to execute when exiting dash state
}

void DashPlayerState::ProcessInput()
{

}

void DashPlayerState::Update(const float& dt)
{
    m_timer -= dt;
    if (m_timer <= 0)
    {
        if (m_entity->isMoving())
            SetNextState<RunPlayerState>();
        else
            SetNextState<IdlePlayerState>();
    }
}

void DashPlayerState::Render(const float& alpha)
{
	// Render logic for dash state
}

//----------------------------------------
//--- AttackPlayerState Implementation ---
//----------------------------------------

AttackPlayerState::AttackPlayerState(MyPlayer* entity) : PlayerStates(entity)
{
}

void AttackPlayerState::OnEnter()
{
	// Logic to execute when entering attack state
    m_entity->shootFireball();
    m_cooldown = 0.2f;

}

void AttackPlayerState::OnExit()
{
	// Logic to execute when exiting attack state
}

void AttackPlayerState::ProcessInput()
{
}

void AttackPlayerState::Update(const float& dt)
{
    m_cooldown -= dt;
    if (m_cooldown <= 0)
    {
        if (m_entity->isMoving())
            SetNextState<RunPlayerState>();
        else
            SetNextState<IdlePlayerState>();
    }
}

void AttackPlayerState::Render(const float& alpha)
{
	// Render logic for attack state
}

//--------------------------------------
//--- RunPlayerState Implementation ---
//--------------------------------------

RunPlayerState::RunPlayerState(MyPlayer* entity) : PlayerStates(entity)
{
}

void RunPlayerState::OnEnter()
{
	// Logic to execute when entering run state
}

void RunPlayerState::OnExit()
{
	// Logic to execute when exiting run state
}

void RunPlayerState::ProcessInput()
{
    
}

void RunPlayerState::Update(const float& dt)
{
    CommonTransitions();

    if (isGoingForward() || isGoingBackward() || isGoingLeft() || isGoingRight())
    {
        SetNextState<IdlePlayerState>();
        return;
    }
}

void RunPlayerState::Render(const float& alpha)
{
	// Render logic for run state
}