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
            "Plane.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
            Ogre::SCENE_DYNAMIC);

        Ogre::Item* ground = sceneManager->createItem(
            "Plane.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
			Ogre::SCENE_DYNAMIC);

        //m_pTtem->setDatablock("Material.001");
        //m_pTtem->setVisibilityFlags(0x000000001);


        const size_t idx = static_cast<size_t>(0);

		//plane

        Ogre::SceneNode* groundNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
            ->createChildSceneNode(Ogre::SCENE_DYNAMIC);

		groundNode->setPosition(0, 0, 0);
        groundNode->setScale(20, 0, 20);

        Ogre::HlmsManager* hlmsManager = mGraphicsSystem->getRoot()->getHlmsManager();
        Ogre::HlmsDatablock* groundMat = hlmsManager->getHlms(Ogre::HLMS_PBS)
            ->createDatablock("PlayerColor",
                "PlayerColor",
                Ogre::HlmsMacroblock(),
                Ogre::HlmsBlendblock(),
                Ogre::HlmsParamVec());

        static_cast<Ogre::HlmsPbsDatablock*>(groundMat)->setDiffuse(Ogre::Vector3(1.0f, 1.0f, 1.0f));
        ground->setDatablock(groundMat);

        groundNode->attachObject(ground);

		auto* plane = new MyPlayer(this, groundNode);
		plane->Init();

        //player

        m_playerNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
            ->createChildSceneNode(Ogre::SCENE_DYNAMIC);

        m_playerNode->setPosition(0, 0, 0);
        m_playerNode->setScale(1, 1, 1);

        /*mSceneNode->roll(Ogre::Radian((Ogre::Real)idx));*/

        m_playerNode->attachObject(m_pTtem);

        Ogre::SceneNode* rootNode = sceneManager->getRootSceneNode();

        // nouvelle sceneNode player

		auto* player = new MyPlayer(this, m_playerNode);
		player->Init();

        m_camera->setTarget(m_playerNode);

        Ogre::Light* light = sceneManager->createLight();
        Ogre::SceneNode* lightNode = rootNode->createChildSceneNode();
        lightNode->attachObject(light);
        lightNode->setPosition(0,150,0 );
        light->setPowerScale(1);
        light->setType(Ogre::Light::LT_DIRECTIONAL);
        light->setDirection(Ogre::Vector3(0, -1, 0).normalisedCopy());

        sceneManager->setAmbientLight(Ogre::ColourValue(0.3f, 0.5f, 0.7f) * 0.1f * 0.75f * 60.0f,
            Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 0.065f * 0.75f * 60.0f,
            -light->getDirection() + Ogre::Vector3::UNIT_Y * 0.2f);

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
