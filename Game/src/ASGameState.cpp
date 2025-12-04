#include "ASGameState.h"

#include <OgreCamera.h>
#include <OgreHlmsPbs.h>
#include <OgreSceneManager.h>

#include "GraphicsSystem.h"
#include "OgreItem.h"
#include "MyCamera.h"
#include "Core/Input.h"


namespace Demo
{
    ArenaShooterGameState::ArenaShooterGameState(const Ogre::String& helpDescription)
        :TutorialGameState(helpDescription)
    {
    }

    //void ArenaShooterGameState::createScene01()
    //{
    //	Ogre::Item* item = mGraphicsSystem->getSceneManager()->createItem(
    //		"Cube_d.mesh", 
    //		Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
    //		Ogre::SCENE_DYNAMIC);
    //	mSceneNode = mGraphicsSystem->getSceneManager()->getRootSceneNode(Ogre::SCENE_DYNAMIC)->createChildSceneNode(Ogre::SCENE_DYNAMIC);
    //	mSceneNode->setPosition(0, 0, 0);
    //	mSceneNode->attachObject(static_cast<Ogre::MovableObject*>(item));
    //}
    void ArenaShooterGameState::createScene01()
    {
        TutorialGameState::createScene01();
		m_camera = new MyCamera(mGraphicsSystem, false);
        Ogre::SceneManager* sceneManager = mGraphicsSystem->getSceneManager();

        mGraphicsSystem->getCamera()->setPosition(Ogre::Vector3(0, 30, 100));

        sceneManager->setForwardClustered(true, 16, 8, 24, 96, 0, 0, 5, 500);


        float armsLength = 2.5f;

        //Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Resources", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        m_pTtem = sceneManager->createItem(
            "cube_d.mesh", Ogre::ResourceGroupManager::AUTODETECT_RESOURCE_GROUP_NAME,
            Ogre::SCENE_DYNAMIC);

        const size_t idx = static_cast<size_t>(0);

        mSceneNode = sceneManager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
            ->createChildSceneNode(Ogre::SCENE_DYNAMIC);

        mSceneNode->setPosition(0, 0, 0);
        mSceneNode->setScale(0.65f, 0.65f, 0.65f);

        mSceneNode->roll(Ogre::Radian((Ogre::Real)idx));

        mSceneNode->attachObject(m_pTtem);

        Ogre::SceneNode* rootNode = sceneManager->getRootSceneNode();

        //Ogre::Light* light = sceneManager->createLight();
        //Ogre::SceneNode* lightNode = rootNode->createChildSceneNode();
        //lightNode->attachObject(light);
        //light->setPowerScale(1.0f);
        //light->setType(Ogre::Light::LT_DIRECTIONAL);
        //light->setDirection(Ogre::Vector3(-1, -1, -1).normalisedCopy());

        //mLightNodes[0] = lightNode;

        //sceneManager->setAmbientLight(Ogre::ColourValue(0.3f, 0.5f, 0.7f) * 0.1f * 0.75f,
        //    Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 0.065f * 0.75f,
        //    -light->getDirection() + Ogre::Vector3::UNIT_Y * 0.2f);

        //light = sceneManager->createLight();
        //lightNode = rootNode->createChildSceneNode();
        //lightNode->attachObject(light);
        //light->setDiffuseColour(0.8f, 0.4f, 0.2f);  // Warm
        //light->setSpecularColour(0.8f, 0.4f, 0.2f);
        //light->setPowerScale(Ogre::Math::PI);
        //light->setType(Ogre::Light::LT_SPOTLIGHT);
        //lightNode->setPosition(-10.0f, 10.0f, 10.0f);
        //light->setDirection(Ogre::Vector3(1, -1, -1).normalisedCopy());
        //light->setAttenuationBasedOnRadius(10.0f, 0.01f);

        //mLightNodes[1] = lightNode;

        //light = sceneManager->createLight();
        //lightNode = rootNode->createChildSceneNode();
        //lightNode->attachObject(light);
        //light->setDiffuseColour(0.2f, 0.4f, 0.8f);  // Cold
        //light->setSpecularColour(0.2f, 0.4f, 0.8f);
        //light->setPowerScale(Ogre::Math::PI);
        //light->setType(Ogre::Light::LT_SPOTLIGHT);
        //lightNode->setPosition(10.0f, 10.0f, -10.0f);
        //light->setDirection(Ogre::Vector3(-1, -1, 1).normalisedCopy());
        //light->setAttenuationBasedOnRadius(10.0f, 0.01f);

        //mLightNodes[2] = lightNode;

        //generateLights();

        //mCameraController = new CameraController(mGraphicsSystem, false);

        //// This sample is too taxing on pixel shaders. Use the fastest PCF filter.
        //Ogre::Hlms* hlms = mGraphicsSystem->getRoot()->getHlmsManager()->getHlms(Ogre::HLMS_PBS);
        //assert(dynamic_cast<Ogre::HlmsPbs*>(hlms));
        //Ogre::HlmsPbs* pbs = static_cast<Ogre::HlmsPbs*>(hlms);
        //pbs->setShadowSettings(Ogre::HlmsPbs::PCF_2x2);

        //// Change the roughness of the default datablock to something prettier.
        //static_cast<Ogre::HlmsPbsDatablock*>(pbs->getDefaultDatablock())->setRoughness(0.1f);

        //TutorialGameState::createScene01();
    }

    void ArenaShooterGameState::update(float timeSinceLast)
    {
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

        m_pTtem->getParentNode()->translate(10 * timeSinceLast, 0, 0);
    }

    void ArenaShooterGameState::keyReleased(const SDL_KeyboardEvent& arg)
    {
        TutorialGameState::keyReleased(arg);
    }
}
