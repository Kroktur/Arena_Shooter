#include "MyCamera.h"

#include "Core/Input.h"
#include "Math/MyMath.h"
#include "Math/Vector3.h"
constexpr float MIN_PITCH = -1.55f;
constexpr float MAX_PITCH = 1.55f;


MyCamera::MyCamera(Demo::GraphicsSystem* graphicsSystem, bool useSceneNode) :
		m_useSceneNode(useSceneNode),
        m_speedModifier(false),
        m_cameraYaw(0),
        m_cameraPitch(0),
		m_sensitivity(0.002f),
        m_cameraBaseSpeed(50),
        m_cameraSpeedBoost(5),
		m_graphicsSystem(graphicsSystem)
{
    // memset is the same as : std::fill(std::begin(m_ZSQD), std::end(m_ZSQD), false);
	memset(m_ZQSD, 0, sizeof(m_ZQSD));               // 0: Z, 1: S, 2: Q, 3: D
	memset(m_directionalCross, 0, sizeof(m_directionalCross)); // 0: Left, 1: Right, 2: Up, 3: Down
	//Camera setup
	// back of player view
    m_camera = m_graphicsSystem->getCamera();
    m_camera->setPosition(0, 10, 0);
	/*m_camera->pitch(-Ogre::Degree(10));*/
    m_camera->setNearClipDistance(0.2f);
    m_camera->setFarClipDistance(1000.0f);
    /*m_camera->lookAt(0, 10, 0);*/
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
    if (!m_target)
        return;
    Ogre::Vector3 playerPos = m_target->getPosition();
    Ogre::Vector3 offset(0, 7.5f, 0);

    m_camera->setPosition(playerPos + offset);
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
    m_cameraYaw -= arg.motion.xrel * m_sensitivity;
    m_cameraPitch -= arg.motion.yrel * m_sensitivity;

    m_cameraPitch = std::max(MIN_PITCH, std::min(MAX_PITCH, m_cameraPitch));

    m_camera->setOrientation(
        Ogre::Quaternion(Ogre::Radian(m_cameraYaw), Ogre::Vector3::UNIT_Y) *
        Ogre::Quaternion(Ogre::Radian(m_cameraPitch), Ogre::Vector3::UNIT_X)
    );
}

Ogre::Vector3 MyCamera::getDirection() const
{
    Ogre::Vector3 dir = m_camera->getDirection();
    dir.y = 0;
    dir.normalise();
    return dir;
}