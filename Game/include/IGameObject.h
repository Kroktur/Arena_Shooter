#pragma once
#include "ASGameState.h"
#include "Core/Component.h"
#include "Core/CompositeCrtp.h"



class IGameObject : public KT::ComponentManager<IGameObject>
{
public:
	IGameObject() : KT::ComponentManager<IGameObject>(this){}
	virtual ~IGameObject() = default;
	virtual void Init() = 0;
	virtual void update(float deltaTime) = 0;
	virtual void input() = 0;
};

