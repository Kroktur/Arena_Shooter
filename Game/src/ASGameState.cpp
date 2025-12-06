#include "ASGameState.h"

#include <OgreCamera.h>
#include <OgreHlmsPbs.h>
#include <OgreSceneManager.h>

#include "GraphicsSystem.h"
#include "OgreItem.h"
#include "MyCamera.h"
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

        mGraphicsSystem->getCamera()->setPosition(Ogre::Vector3(0, 0, 10));

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

        mSceneNode->roll(Ogre::Radian((Ogre::Real)idx));

        mSceneNode->attachObject(m_pTtem);

        Ogre::SceneNode* rootNode = sceneManager->getRootSceneNode();



        Ogre::Light* light = sceneManager->createLight();
        Ogre::SceneNode* lightNode = rootNode->createChildSceneNode();
        lightNode->attachObject(light);
        lightNode->setPosition(0, 0, 10);
        light->setPowerScale(97.0f);
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
        KT::Input::Update();


        //input
        if (m_camera)
            m_camera->Input();
        //update
        if (m_camera)
            m_camera->update(timeSinceLast);
       /* TutorialGameState::update(timeSinceLast);*/
        if (mDisplayHelpMode != 0)
        {
            // Show FPS
            Ogre::String finalText;
            generateDebugText(timeSinceLast, finalText);
          /*  mDebugText->setCaption(finalText);
            mDebugTextShadow->setCaption(finalText);*/
        }

        if (m_camera)
            m_camera->update(timeSinceLast);

        //m_pTtem->getParentNode()->translate(10 * timeSinceLast, 0, 0);
    }

    void ArenaShooterGameState::keyReleased(const SDL_KeyboardEvent& arg)
    {
        TutorialGameState::keyReleased(arg);
    }
}
