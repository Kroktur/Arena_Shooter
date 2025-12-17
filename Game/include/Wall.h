#pragma once
#include "ASGameState.h"
#include "GameComponent.h"
#include "IGameObject.h"
#include "MyMeshReader.h"
#include "Core/CompositeCrtp.h"
#include "Core/Input.h"
#include "Core/StateMachine.h"


class Wall : public IGameObject, public KT::CompositeCRTP<Wall, IGameObject, Demo::ArenaShooterGameState>
{
public:
	Wall(KT::IComposite<IGameObject, Demo::ArenaShooterGameState>* owner, const KT::Vector3F& position, const KT::Vector3F& size) : KT::CompositeCRTP<Wall, IGameObject, Demo::ArenaShooterGameState>(owner), m_position(position), m_size(size)
	{

	}
	void update(float deltaTime) override{}
	void Exit() override
	{
		
	}
	void input() override{}
	void Init() override
	{
		auto Amin = m_position - m_size;
		auto Amax = m_position + m_size;
		auto AABB = KT::AABB3DF(Amin,Amax);
		auto obb = KT::OBB3DF(AABB.GetPts());
		auto collide = AddComponent<CollisionComponent<IGameObject>>();
		collide->AddObb(obb);
	}
private:
	KT::Vector3F m_position;
	KT::Vector3F m_size;
};
