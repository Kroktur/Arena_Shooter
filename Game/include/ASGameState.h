#ifndef ARENASHOOTERSTATE
#define ARENASHOOTERSTATE

#include "IGameObject.h"
#include "OgreOverlayPrerequisites.h"
#include "OgrePrerequisites.h"
#include "TutorialGameState.h"

#include "OgreCommon.h"
#include "MyCamera.h"
#include "Core/CompositeCrtp.h"

namespace Demo
{


	class ArenaShooterGameState : public TutorialGameState , public KT::ExcludeRootCRTP<ArenaShooterGameState,IGameObject,ArenaShooterGameState>
	{
		MyCamera* m_camera;
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