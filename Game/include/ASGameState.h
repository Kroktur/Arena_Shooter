#ifndef ARENASHOOTERSTATE
#define ARENASHOOTERSTATE

#include "IGameObject.h"
#include "OgreOverlayPrerequisites.h"
#include "OgrePrerequisites.h"
#include "TutorialGameState.h"

#include "OgreCommon.h"
#include "MyCamera.h"
#include "NodePull.h"
#include "Core/CompositeCrtp.h"

namespace Demo
{
	class ArenaShooterGameState : public TutorialGameState , public KT::ExcludeRootCRTP<ArenaShooterGameState,IGameObject,ArenaShooterGameState>
	{
		MyCamera* m_camera;
		Ogre::Item* m_pTtem;


	private:
		Ogre::SceneNode* mSceneNode;
		Ogre::SceneNode* m_playerNode;
		Ogre::SceneManager* m_manager;
		std::vector<std::function<void()>> instantiate;
		void ExecuteBegin();
	public:
	/*	void DetachItem(int nodeIndex, int itemIndex);

		int RegisterItem();
		Ogre::Item* GetItem(int index);
		void DestroyItem(int index);*/
		ArenaShooterGameState(const Ogre::String& helpDescription);
		~ArenaShooterGameState();
		void createScene01() override;

		void update(float timeSinceLast) override;

		void keyReleased(const SDL_KeyboardEvent& arg) override;
		Ogre::SceneManager* GetSceneManager();
		void destroyScene() override;
		void deinitialize() override;
		void ToDoAtBegin(std::function<void()> fn);
	
	};
}
#endif