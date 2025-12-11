#include "PlayerStates.h"
#include "Core/Input.h"

PlayerStates::PlayerStates(MyPlayer* entity) : KT::IState<MyPlayer>(entity)
{}

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
    // Jump
    if (KT::Input::isPressed<KT::KEY>(KT::KEY::SPACE))
    {
        SetNextState<JumpPlayerState>();
        return;
    }

    // Attack
    if (KT::Input::isPressed<KT::MOUSE>(KT::MOUSE::LHS))
    {
        SetNextState<AttackPlayerState>();
        return;
    }

    // Dash
    bool anyMoveKey =
        KT::Input::isPressed<KT::KEY>(KT::KEY::Z) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::Q) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::S) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::D);

    if (anyMoveKey && KT::Input::isPressed<KT::KEY>(KT::KEY::LSHIFT))
    {
        SetNextState<DashPlayerState>();
        return;
    }

    // Run
    if (anyMoveKey)
    {
        SetNextState<RunPlayerState>();
        return;
    }
}

void IdlePlayerState::Update(const float& dt)
{
	// Update logic for idle state
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
    bool anyMoveKey =
        KT::Input::isPressed<KT::KEY>(KT::KEY::Z) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::Q) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::S) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::D);

    // go idle
    if (!anyMoveKey)
    {
        SetNextState<IdlePlayerState>();
        return;
    }

    // go jump
    if (KT::Input::isPressed<KT::KEY>(KT::KEY::SPACE))
    {
        SetNextState<JumpPlayerState>();
        return;
    }

    // attack
    if (KT::Input::isPressed<KT::MOUSE>(KT::MOUSE::LHS))
    {
        SetNextState<AttackPlayerState>();
        return;
    }

    // dash
    if (KT::Input::isPressed<KT::KEY>(KT::KEY::LSHIFT))
    {
        SetNextState<DashPlayerState>();
        return;
    }
}

void JumpPlayerState::Update(const float& dt)
{
	// Update logic for jump state

	/*SetNextState<IdlePlayerState>();*/
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
}

void DashPlayerState::OnExit()
{
	// Logic to execute when exiting dash state
}

void DashPlayerState::ProcessInput()
{
    bool anyMoveKey =
        KT::Input::isPressed<KT::KEY>(KT::KEY::Z) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::Q) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::S) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::D);

    // go idle
    if (!anyMoveKey)
    {
        SetNextState<IdlePlayerState>();
        return;
    }

    // Run
    if (anyMoveKey)
    {
        SetNextState<RunPlayerState>();
        return;
    }

    // go jump
    if (KT::Input::isPressed<KT::KEY>(KT::KEY::SPACE))
    {
        SetNextState<JumpPlayerState>();
        return;
    }

    // attack
    if (KT::Input::isPressed<KT::MOUSE>(KT::MOUSE::LHS))
    {
        SetNextState<AttackPlayerState>();
        return;
    }
}

void DashPlayerState::Update(const float& dt)
{
	// Update logic for dash state
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
}

void AttackPlayerState::OnExit()
{
	// Logic to execute when exiting attack state
}

void AttackPlayerState::ProcessInput()
{
    bool anyMoveKey =
        KT::Input::isPressed<KT::KEY>(KT::KEY::Z) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::Q) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::S) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::D);

    // go idle
    if (!anyMoveKey)
    {
        SetNextState<IdlePlayerState>();
        return;
    }

    // Run
    if (anyMoveKey)
    {
        SetNextState<RunPlayerState>();
        return;
    }

    // go jump
    if (KT::Input::isPressed<KT::KEY>(KT::KEY::SPACE))
    {
        SetNextState<JumpPlayerState>();
        return;
    }

    if (KT::Input::isPressed<KT::KEY>(KT::KEY::LSHIFT))
    {
        SetNextState<DashPlayerState>();
        return;
    }
}

void AttackPlayerState::Update(const float& dt)
{
	// Update logic for attack state
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
    bool anyMoveKey =
        KT::Input::isPressed<KT::KEY>(KT::KEY::Z) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::Q) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::S) ||
        KT::Input::isPressed<KT::KEY>(KT::KEY::D);

    // go idle
    if (!anyMoveKey)
    {
        SetNextState<IdlePlayerState>();
        return;
    }

    // go jump
    if (KT::Input::isPressed<KT::KEY>(KT::KEY::SPACE))
    {
        SetNextState<JumpPlayerState>();
        return;
    }

    // dash
    if (KT::Input::isPressed<KT::KEY>(KT::KEY::LSHIFT))
    {
        SetNextState<DashPlayerState>();
        return;
    }

    // attack
    if (KT::Input::isPressed<KT::MOUSE>(KT::MOUSE::LHS))
    {
        SetNextState<AttackPlayerState>();
        return;
    }
}

void RunPlayerState::Update(const float& dt)
{
	// Update logic for run state
}

void RunPlayerState::Render(const float& alpha)
{
	// Render logic for run state
}