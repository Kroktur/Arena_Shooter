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
#include "ofbx.h"
#include "fbxLoader.h"
#include "MyParser.h"
#include "OgreMesh2.h"

namespace Demo
{


	ArenaShooterGameState::ArenaShooterGameState(const Ogre::String& helpDescription)
        :TutorialGameState(helpDescription)
    {
       
    }

	ArenaShooterGameState::~ArenaShooterGameState()
	{
        /*  ExecuteAction([&](IGameObject* go)
            {
                go->Exit();
            });*/
	}

	void ArenaShooterGameState::createScene01()
    {
        TutorialGameState::createScene01();
        m_manager = mGraphicsSystem->getSceneManager();

		m_camera = new MyCamera(mGraphicsSystem, false);
      
        // INIT ALL PULL 
        m_manager->setForwardClustered(true, 16, 8, 24, 96, 0, 0, 5, 500);
      
        auto item3 = ItemPull::Type::PullValidObjectWithCondition(ItemPull::create, [](Ogre::Item* node) {return ItemPull::ConditionStr(node, "CubeFromMedia_d.mesh"); }, m_manager, "CubeFromMedia_d.mesh");
    
        auto node3 = NodePull::Type::PullValidObject(NodePull::create, m_manager);
        //GameState::createScene01();
        
        const char* fbxPath = "../../FBXFile/montage_map.fbx";
        auto fileData = FBXReader::loadFile(fbxPath);
        ofbx::IScene* scene = ofbx::load(fileData.data(), (ofbx::usize)fileData.size(), static_cast<ofbx::u16>(ofbx::LoadFlags::NONE), nullptr, nullptr);


        std::vector<Ogre::Item *> m_Items;
        std::vector<Ogre::Node*> m_sceneNodes;

        if (!scene)
            throw std::runtime_error("Failed to parse FBX file");

        int loadedCount = 0;
        int meshc = scene->getMeshCount();
        for (int i = 0; i < meshc; i++)
        {
            const ofbx::Mesh* mesh = scene->getMesh(i);
            Ogre::Item* item = createItemFromFBX(m_manager, mesh, i);
            if (item)
            {
                //getMaterialFromFBX(item, mesh, i, mGraphicsSystem);
                Ogre::SceneNode* node = m_manager->getRootSceneNode(Ogre::SCENE_DYNAMIC)
                    ->createChildSceneNode(Ogre::SCENE_DYNAMIC);

                ofbx::DMatrix globalTransform = mesh->getGlobalTransform();

                Ogre::Vector3 position;
                Ogre::Quaternion rotation;
                Ogre::Vector3 scale;

                FBXReader::extractTransform(globalTransform, position, rotation, scale);

                node->setPosition(position);
                node->setOrientation(rotation);
                node->setScale(scale);
                node->attachObject(item);

                m_Items.push_back(item);
                m_sceneNodes.push_back(node);

                loadedCount++;
            }
        }
        if (loadedCount == 0)
            throw std::runtime_error("No valid meshes found in FBX");
        scene->destroy();

        node3.second->setPosition(0, -10, 0);
        node3.second->setScale(100, 1, 100);

        item3.second->setDatablock("Marble");
        node3.second->attachObject(item3.second);
        Ogre::SceneNode* rootNode = m_manager->getRootSceneNode();
        new MyPlayer(this);

        ExecuteAction([&](IGameObject* go)
            {
                go->Init();
            });

        Ogre::Light* light = m_manager->createLight();
        Ogre::SceneNode* lightNode = rootNode->createChildSceneNode();
        lightNode->attachObject(light);
        lightNode->setPosition(0, 150, 0);
        light->setPowerScale(1);
        light->setType(Ogre::Light::LT_DIRECTIONAL);
        light->setDirection(Ogre::Vector3(0, -1, 0).normalisedCopy());
        m_manager->setAmbientLight(Ogre::ColourValue(0.3f, 0.5f, 0.7f) * 0.1f * 0.75f * 60.0f,
            Ogre::ColourValue(0.6f, 0.45f, 0.3f) * 0.065f * 0.75f * 60.0f,
            -light->getDirection() + Ogre::Vector3::UNIT_Y * 0.2f);

}

void ArenaShooterGameState::update(float timeSinceLast)
{
    ExecuteBegin();
    //input
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

        if (mDisplayHelpMode != 0)
        {
            // Show FPS
            Ogre::String finalText;
            generateDebugText(timeSinceLast, finalText);


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
            toDelet[i]->AsBase()->Exit();
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

    void ArenaShooterGameState::destroyScene()
    {
            ExecuteAction([&](IGameObject* go)
            {
                go->Exit();
            });
        TutorialGameState::destroyScene();
    }

    void ArenaShooterGameState::deinitialize()
    {
	    TutorialGameState::deinitialize();
    }

    void ArenaShooterGameState::ToDoAtBegin(std::function<void()> fn)
    {
        instantiate.push_back(fn);
    }

    void ArenaShooterGameState::ExecuteBegin()
    {
        for (auto& fn : instantiate)
            fn();
        instantiate.clear();
    }
}
