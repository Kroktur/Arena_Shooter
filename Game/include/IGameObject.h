#pragma once
#include "ASGameState.h"
#include "Core/Component.h"
#include "Core/CompositeCrtp.h"


namespace Demo
{
	class ArenaShooterGameState;
}

class IGameObject : public KT::ComponentManager<IGameObject>
{
public:
	IGameObject() : KT::ComponentManager<IGameObject>(this){}
	virtual ~IGameObject() = default;
	virtual void Init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void input() = 0;
};


template  <typename derived>
using compositeGO = KT::CompositeCRTP<derived,IGameObject,Demo::ArenaShooterGameState>;

template  <typename derived>
using leafGO = KT::CompositeCRTP<derived, IGameObject, Demo::ArenaShooterGameState>;