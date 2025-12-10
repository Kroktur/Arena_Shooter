#include "MyCamera.h"

#include "Core/Input.h"
#include "Math/MyMath.h"
constexpr float MIN_PITCH = -1.55f;
constexpr float MAX_PITCH = 1.55f;


MyCamera::MyCamera(Demo::GraphicsSystem* graphicsSystem, bool useSceneNode) :
		m_useSceneNode(useSceneNode),
        m_speedModifier(false),
        m_cameraYaw(0),
        m_cameraPitch(0),
        m_cameraBaseSpeed(50),
        m_cameraSpeedBoost(5),
		m_graphicsSystem(graphicsSystem)
{
    // memset is the same as : std::fill(std::begin(m_ZSQD), std::end(m_ZSQD), false);
	memset(m_ZQSD, 0, sizeof(m_ZQSD));               // 0: Z, 1: S, 2: Q, 3: D
	memset(m_directionalCross, 0, sizeof(m_directionalCross)); // 0: Left, 1: Right, 2: Up, 3: Down
	//Camera setup
	// top down view
    /*m_camera = m_graphicsSystem->getCamera();
    m_camera->setPosition(0, 10, 0);
	m_camera->pitch(-Ogre::Degree(10));
    m_camera->setNearClipDistance(0.2f);
    m_camera->setFarClipDistance(1000.0f);*/

	// back of player view
    m_camera = m_graphicsSystem->getCamera();
    m_camera->setPosition(0, 30, 0);
    m_camera->pitch(-Ogre::Degree(90));
    m_camera->setNearClipDistance(0.2f);
    m_camera->setFarClipDistance(1000.0f);
 //   cameraNode->setPosition(0, 100, 0);
}

Ogre::Camera* MyCamera::getCamera() const
{
    return m_camera;
}

void MyCamera::setTarget(Ogre::SceneNode* target)
{
    m_target = target;
}

void MyCamera::update(const float& dt)
{
	/*Ogre::Camera* camera = m_graphicsSystem->getCamera();
    Ogre::Node* cameraNode = m_useSceneNode ? camera->getParentNode() : nullptr;*/
  /*  if (m_cameraYaw != 0.0f || m_cameraPitch != 0.0f)
    {
	    if (m_useSceneNode)
	    {
            cameraNode->yaw(Ogre::Radian(m_cameraYaw), Ogre::Node::TS_WORLD);
            cameraNode->pitch(Ogre::Radian(m_cameraPitch));
	    }
        else
        {
            camera->yaw(Ogre::Radian(m_cameraYaw));
            camera->pitch(Ogre::Radian(m_cameraPitch));
        }

        m_cameraYaw = 0.0f;
        m_cameraPitch = 0.0f;
    }*/

  //  static bool init = false;
  //  if (!init)
  //  {
  //      //cameraNode->pitch(Ogre::Degree(90), Ogre::Node::TS_WORLD);
  //      camera->pitch(-Ogre::Degree(90));
		//init = true;
  //  }

	// --- Movement ---
    /*int camMovementZ = m_directionalCross[2] - m_directionalCross[0];
    int camMovementX = m_directionalCross[3] - m_directionalCross[1];
    int slideUpDown  = m_directionalCross[0] - m_directionalCross[1];

    float speed = m_cameraBaseSpeed;*/

    /*if (camMovementX || slideUpDown || camMovementZ)
    {
        Ogre::Vector3 dir((float)camMovementX, (float)slideUpDown, (float)-camMovementZ);
        dir.normalise();

        float speed = m_cameraBaseSpeed;
        if (m_speedModifier)
            speed *= m_cameraSpeedBoost;

        dir *= speed * dt;

        if (m_useSceneNode)
            cameraNode->translate(dir, Ogre::Node::TS_LOCAL);
        else
            camera->moveRelative(dir);
    }*/

    //Ogre::Vector3 dir((float)camMovementX, 0.0f, (float)-camMovementZ);

    //dir.normalise();
    //dir *= speed * dt;

    //camera->move(dir); // TS_WORLD

    if (!m_target)
        return;

    Ogre::Vector3 playerPos = m_target->getPosition();
    Ogre::Vector3 offset(0, 30, -20);
    float smooth = 5.0f;
    Ogre::Vector3 current = m_camera->getPosition();
    Ogre::Vector3 target = playerPos + offset;

    Ogre::Vector3 newPos = current + (target - current) * smooth * dt;

    m_camera->setPosition(newPos);
    m_camera->lookAt(playerPos);
}

bool MyCamera::keyPressed(const SDL_KeyboardEvent& arg)
{/*
    if (arg.keysym.scancode == SDL_SCANCODE_LSHIFT)
        m_speedModifier = true;

    if (KT::Input::isPressed<KT::KEY>(KT::KEY::UP))
        m_directionalCross[0] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::LEFT))
        m_directionalCross[1] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::DOWN))
        m_directionalCross[2] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::RIGHT))
        m_directionalCross[3] = true;
    else
        return false;*/
    return true;
}

bool MyCamera::keyReleased(const SDL_KeyboardEvent& arg)
{/*
    if (arg.keysym.scancode == SDL_SCANCODE_LSHIFT)
        m_speedModifier = false;

    if (!KT::Input::isPressed<KT::KEY>(KT::KEY::UP))
        m_directionalCross[0] = false;
    else if (!KT::Input::isPressed<KT::KEY>(KT::KEY::LEFT))
        m_directionalCross[1] = false;
    else if (!KT::Input::isPressed<KT::KEY>(KT::KEY::DOWN))
        m_directionalCross[2] = false;
    else if (!KT::Input::isPressed<KT::KEY>(KT::KEY::RIGHT))
        m_directionalCross[3] = false;
    else
        return false;*/
    return true;
}

void MyCamera::Input()
{
  /*  m_directionalCross[0] = false;
    m_directionalCross[1] = false;
    m_directionalCross[2] = false;
    m_directionalCross[3] = false;
    if (KT::Input::isPressed<KT::KEY>(KT::KEY::UP))
        m_directionalCross[0] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::LEFT))
        m_directionalCross[1] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::DOWN))
        m_directionalCross[2] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::RIGHT))
        m_directionalCross[3] = true;*/
}

void MyCamera::onMouseMoved(const SDL_Event& arg)
{
    //constexpr float sensitivity = 0.15f;

    //m_cameraYaw += -arg.motion.xrel * sensitivity * 0.002f;
    //m_cameraPitch += -arg.motion.yrel * sensitivity * 0.002f;

    //// Clamp pitch
    //m_cameraPitch = KT::Math::Clamp(m_cameraPitch, MIN_PITCH, MAX_PITCH);
}
