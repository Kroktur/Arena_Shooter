#pragma once
#include "ASGameState.h"
#include "GameComponent.h"
#include "IGameObject.h"
#include "Core/CompositeCrtp.h"
#include "Core/Input.h"
#include "Core/StateMachine.h"


class Fox : public IGameObject, public KT::CompositeCRTP<Fox, IGameObject, Demo::ArenaShooterGameState>
{
public:
	Fox(KT::IComposite<IGameObject, Demo::ArenaShooterGameState>* owner);
	~Fox() override = default;
	void Init() override;
	void Exit() override;
	void update(float deltaTime) override;
	void input() override{}
};