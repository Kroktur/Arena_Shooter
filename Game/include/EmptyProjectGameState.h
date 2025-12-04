#ifndef ARENASHOOTERSTATE
#define ARENASHOOTERSTATE

#include "OgreOverlayPrerequisites.h"
#include "OgrePrerequisites.h"
#include "TutorialGameState.h"

#include "OgreCommon.h"

namespace Demo
{


	class ArenaShooterGameState : public TutorialGameState
	{

		Ogre::Item* m_pTtem;


	private:
		Ogre::SceneNode* mSceneNode;
	public:
		ArenaShooterGameState(const Ogre::String& helpDescription);

		void createScene01() override;

		void update(float timeSinceLast) override;

		void keyReleased(const SDL_KeyboardEvent& arg) override;

	};
}
#endif