#pragma once

#include "ASGameState.h"
#include "GameComponent.h"
#include "IGameObject.h"
#include "Core/CompositeCrtp.h"
#include "Core/Input.h"
#include "Core/StateMachine.h"

class MapTile : public IGameObject, public KT::CompositeCRTP<MapTile, IGameObject, Demo::ArenaShooterGameState>
{
public:
	MapTile(KT::IComposite<IGameObject, Demo::ArenaShooterGameState>* owner,Ogre::SceneNode* node, Ogre::Item* item);
	~MapTile() override = default;
	void Init() override;
	void Exit() override;
	void update(float deltaTime) override;
	void input() override;
};
	//	// --- getters ---