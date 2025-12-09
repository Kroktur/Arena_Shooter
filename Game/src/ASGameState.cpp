#include "ASGameState.h"

#include <OgreCamera.h>
#include <OgreHlmsPbs.h>
#include <OgreSceneManager.h>

#include "GraphicsSystem.h"
#include "OgreItem.h"
#include "MyCamera.h"
#include "MyPlayer.h"
#include "NodePull.h"
#include "Core/Input.h"
#include "OgreTextureGpuManager.h"
#include "OgreTextureFilters.h"

#include "OgreHlmsManager.h"
#include "OgreHlmsPbs.h"

#include "OgreHlmsPbsDatablock.h"
#include "OgreHlmsSamplerblock.h"
#include "Tools/Chrono.h"

namespace Demo
{


	ArenaShooterGameState::ArenaShooterGameState(const Ogre::String& helpDescription)
        :TutorialGameState(helpDescription)
    {
       
    }
    void ArenaShooterGameState::createScene01()
    {
        TutorialGameState::createScene01();
        m_manager = mGraphicsSystem->getSceneManager();


		m_camera = new MyCamera(mGraphicsSystem, false);
      
        // INIT ALL PULL 

        //mGraphicsSystem->getCamera()->setPosition(Ogre::Vector3(0, 0, 50));

        m_manager->setForwardClustered(true, 16, 8, 24, 96, 0, 0, 5, 500);


        auto item = ItemPull::Type::PullValidObjectWithCondition(ItemPull::create, [](Ogre::Item* node) {return ItemPull::ConditionStr(node, "Plane.mesh"); }, m_manager, "Plane.mesh");
        auto item2 = ItemPull::Type::PullValidObjectWithCondition(ItemPull::create, [](Ogre::Item* node) {return ItemPull::ConditionStr(node, "Plane.mesh"); }, m_manager,"Plane.mesh" );
        auto item3 = ItemPull::Type::PullValidObjectWithCondition(ItemPull::create, [](Ogre::Item* node) {return ItemPull::ConditionStr(node, "CubeFromMedia_d.mesh"); }, m_manager, "CubeFromMedia_d.mesh");
        //m_pTtem->setDatablock("Material.001");
        //m_pTtem->setVisibilityFlags(0x000000001);


        const size_t idx = static_cast<size_t>(0);

        
        auto node = NodePull::Type::PullValidObject(NodePull::create,m_manager);
        auto node2 = NodePull::Type::PullValidObject(NodePull::create, m_manager);
        auto node3 = NodePull::Type::PullValidObject(NodePull::create, m_manager);
        node.second->setPosition(0, 0, 0);
        node.second->setScale(10, 10, 10);


        /*mSceneNode->roll(Ogre::Radian((Ogre::Real)idx));*/

        node.second->attachObject(item.second);

        node2.second->setPosition(0, 0, 0);
        node2.second->setScale(10, 10, 10);


        /*mSceneNode->roll(Ogre::Radian((Ogre::Real)idx));*/

        node2.second->attachObject(item2.second);


        node3.second->setPosition(0, -10, 0);
        node3.second->setScale(100, 1, 100);


        /*mSceneNode->roll(Ogre::Radian((Ogre::Real)idx));*/
        item3.second->setDatablock("Marble");
        node3.second->attachObject(item3.second);


        Ogre::SceneNode* rootNode = m_manager->getRootSceneNode();

        // nouvelle sceneNode player


		auto* player = new MyPlayer(this, node.second);
		player->Init();


        Ogre::Light* light = m_manager->createLight();
        Ogre::SceneNode* lightNode = rootNode->createChildSceneNode();
        lightNode->attachObject(light);
        lightNode->setPosition(0,150,0 );
        light->setPowerScale(1);
        light->setType(Ogre::Light::LT_DIRECTIONAL);
        light->setDirection(Ogre::Vector3(0, -1, 0).normalisedCopy());

        m_manager->setAmbientLight(Ogre::ColourValue(0.3f, 0.5f, 0.7f) * 0.1f * 0.75f * 60.0f,
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

        static KT::Chrono<float> destroy;




        std::vector<IComponent*> toDelet;
        //logic here
        ExecuteAction([&](IComponent* component)
        {
        	auto go = component->AsBase();
            if (!go)
                return;
            if (!go->HasComponent<LivingComponent<IGameObject>>())
                return;
            auto life = go->GetComponent<LivingComponent<IGameObject>>();
            if (!life->IsLiving())
                toDelet.push_back(component);
        });
        for (int i = (static_cast<int>(toDelet.size()) - 1); i >= 0 ; --i)
        {
            delete toDelet[i];
        }
        toDelet.clear();

    }

    void ArenaShooterGameState::keyReleased(const SDL_KeyboardEvent& arg)
    {
       // TutorialGameState::keyReleased(arg);
    }

    Ogre::SceneManager* ArenaShooterGameState::GetSceneManager()
    {
        return m_manager;
    }
}
