#include "ASGameState.h"

#include <OgreCamera.h>
#include <OgreHlmsPbs.h>
#include <OgreSceneManager.h>

#include "GraphicsSystem.h"
#include "OgreItem.h"
#include "MyCamera.h"
#include "MyPlayer.h"
#include "Core/Input.h"
#include "OgreTextureGpuManager.h"
#include "OgreTextureFilters.h"

#include "OgreHlmsManager.h"
#include "OgreHlmsPbs.h"

#include "OgreHlmsPbsDatablock.h"
#include "OgreHlmsSamplerblock.h"

namespace Demo
{
    ArenaShooterGameState::ArenaShooterGameState(const Ogre::String& helpDescription)
        :TutorialGameState(helpDescription)
    {
    }
    void ArenaShooterGameState::createScene01()
    {
        TutorialGameState::createScene01();
		m_camera = new MyCamera(mGraphicsSystem, false);
        Ogre::SceneManager* sceneManager = mGraphicsSystem->getSceneManager();

        //mGraphicsSystem->getCamera()->setPosition(Ogre::Vector3(0, 0, 50));

        sceneManager->setForwardClustered(true, 16, 8, 24, 96, 0, 0, 5, 500);



        m_pTtem = sceneManager->createItem(
            "CubeFromMedia_d.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
            Ogre::SCENE_DYNAMIC);

        m_pTtem->setDatablock("Marble");
        m_pTtem->setVisibilityFlags(0x000000001);


        const size_t idx = static_cast<size_t>(0);

        mSceneNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
            ->createChildSceneNode(Ogre::SCENE_DYNAMIC);

        mSceneNode->setPosition(0, 0, 0);
        mSceneNode->setScale(0.65f, 0.65f, 0.65f);

        /*mSceneNode->roll(Ogre::Radian((Ogre::Real)idx));*/

        mSceneNode->attachObject(m_pTtem);

        Ogre::SceneNode* rootNode = sceneManager->getRootSceneNode();

        // nouvelle sceneNode player


		auto* player = new MyPlayer(this, mSceneNode);
		player->Init();
    }

    void ArenaShooterGameState::update(float timeSinceLast)
    {
        //TODO GameLoop here !!



		// don't touch
     

        //input
      /*  if (m_camera)
            m_camera->Input();*/
        KT::Input::Update();
        ExecuteAction([](IGameObject* go)
            {
                go->input();
            });
        //update
        if (m_camera)
            m_camera->update(timeSinceLast);
        ExecuteAction([&](IGameObject* go)
            {
                go->update(timeSinceLast);
            });

       /* TutorialGameState::update(timeSinceLast);*/
        if (mDisplayHelpMode != 0)
        {
            // Show FPS
            Ogre::String finalText;
            generateDebugText(timeSinceLast, finalText);
          /*  mDebugText->setCaption(finalText);
            mDebugTextShadow->setCaption(finalText);*/
        }
    }

    void ArenaShooterGameState::keyReleased(const SDL_KeyboardEvent& arg)
    {
       // TutorialGameState::keyReleased(arg);
    }
}
