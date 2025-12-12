#include "PlayerStates.h"
#include "Core/Input.h"
#include "MyPlayer.h"
#include "MyCamera.h"

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

bool PlayerStates::isRunning()
{
    return KT::Input::isPressed<KT::KEY>(KT::KEY::LCTRL);
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
        SetNextState<DashPlayerState>();
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

    bool moving = isGoingForward() || isGoingBackward() || isGoingLeft() || isGoingRight();

    if (moving)
    {
        if (isRunning())
            SetNextState<RunPlayerState>();
        else
            SetNextState<WalkPlayerState>();
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
    m_entity->m_isGrounded = false;
    m_entity->m_verticalVelocity = m_entity->m_jumpForce;
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
        {
            if (isRunning())
                SetNextState<RunPlayerState>();
            else
                SetNextState<WalkPlayerState>();
        }
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
    m_timer = 2.0f;
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
//--- WalkPlayerState Implementation ---
//--------------------------------------

WalkPlayerState::WalkPlayerState(MyPlayer* entity) : PlayerStates(entity)
{
}

void WalkPlayerState::OnEnter()
{
    // Logic to execute when entering run state
    m_entity->m_currentSpeed = m_entity->m_walkSpeed;
    /*m_entity->getCamera()->setFov(100.0f);*/
}

void WalkPlayerState::OnExit()
{
    // Logic to execute when exiting run state
}

void WalkPlayerState::ProcessInput()
{

}

void WalkPlayerState::Update(const float& dt)
{
    CommonTransitions();

    bool moving = isGoingForward() || isGoingBackward() || isGoingLeft() || isGoingRight();

    if (!moving)
    {
        SetNextState<IdlePlayerState>();
        return;
    }

    if (isRunning())
        SetNextState<RunPlayerState>();
}

void WalkPlayerState::Render(const float& alpha)
{
    // Render logic for run state
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
    m_entity->m_currentSpeed = m_entity->m_runSpeed;
    /*m_entity->getCamera()->setFov(110.0f);*/
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

    bool moving = isGoingForward() || isGoingBackward() || isGoingLeft() || isGoingRight();

    if (!moving)
    {
        SetNextState<IdlePlayerState>();
        return;
    }

    if (!isRunning())
        SetNextState<WalkPlayerState>();

}

void RunPlayerState::Render(const float& alpha)
{
	// Render logic for run state
}