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
        m_cameraBaseSpeed(10),
        m_cameraSpeedBoost(5),
		m_graphicsSystem(graphicsSystem)
{
    // memset is the same as : std::fill(std::begin(m_ZSQD), std::end(m_ZSQD), false);
	memset(m_ZQSD, 0, sizeof(m_ZQSD));               // 0: Z, 1: S, 2: Q, 3: D
	memset(m_slideUpDown, 0, sizeof(m_slideUpDown)); // 0: Up, 1: Down
}

Ogre::Camera* MyCamera::getCamera() const
{
    return m_camera;
}

void MyCamera::update(const float& dt)
{
	Ogre::Camera* camera = m_graphicsSystem->getCamera();
    Ogre::Node* cameraNode = m_useSceneNode ? camera->getParentNode() : nullptr;
    if (m_cameraYaw != 0.0f || m_cameraPitch != 0.0f)
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
    }

	// --- Movement ---
    int camMovementZ = m_ZQSD[2] - m_ZQSD[0];
    int camMovementX = m_ZQSD[3] - m_ZQSD[1];
    int slideUpDown = m_slideUpDown[0] - m_slideUpDown[1];

    if (camMovementX || slideUpDown || camMovementZ)
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
    }
}

bool MyCamera::keyPressed(const SDL_KeyboardEvent& arg)
{
    if (arg.keysym.scancode == SDL_SCANCODE_LSHIFT)
        m_speedModifier = true;
    if (KT::Input::isPressed<KT::KEY>(KT::KEY::Z))
        m_ZQSD[0] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::Q))
        m_ZQSD[1] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::S))
        m_ZQSD[2] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::D))
        m_ZQSD[3] = true;
    else if (arg.keysym.scancode == SDL_SCANCODE_PAGEUP)
        m_slideUpDown[0] = true;
    else if (arg.keysym.scancode == SDL_SCANCODE_PAGEDOWN)
        m_slideUpDown[1] = true;
    else
        return false;
    return true;
}




bool MyCamera::keyReleased(const SDL_KeyboardEvent& arg)
{
    if (arg.keysym.scancode == SDL_SCANCODE_LSHIFT)
        m_speedModifier = false;

    if (!KT::Input::isPressed<KT::KEY>(KT::KEY::Z))
        m_ZQSD[0] = false;
    else if (!KT::Input::isPressed<KT::KEY>(KT::KEY::Q))
        m_ZQSD[1] = false;
    else if (!KT::Input::isPressed<KT::KEY>(KT::KEY::S))
        m_ZQSD[2] = false;
    else if (!KT::Input::isPressed<KT::KEY>(KT::KEY::D))
        m_ZQSD[3] = false;
    else if (arg.keysym.scancode == SDL_SCANCODE_PAGEUP)
        m_slideUpDown[0] = false;
    else if (arg.keysym.scancode == SDL_SCANCODE_PAGEDOWN)
        m_slideUpDown[1] = false;
    else
        return false;
    return true;
}

void MyCamera::Input()
{
    m_ZQSD[0] = false;
    m_ZQSD[1] = false;
    m_ZQSD[2] = false;
    m_ZQSD[3] = false;
    if (KT::Input::isPressed<KT::KEY>(KT::KEY::Z))
        m_ZQSD[0] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::Q))
        m_ZQSD[1] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::S))
        m_ZQSD[2] = true;
    else if (KT::Input::isPressed<KT::KEY>(KT::KEY::D))
        m_ZQSD[3] = true;
}

void MyCamera::onMouseMoved(const SDL_Event& arg)
{
    constexpr float sensitivity = 0.15f;

    m_cameraYaw += -arg.motion.xrel * sensitivity * 0.002f;
    m_cameraPitch += -arg.motion.yrel * sensitivity * 0.002f;

    // Clamp pitch
    m_cameraPitch = KT::Math::Clamp(m_cameraPitch, MIN_PITCH, MAX_PITCH);
}
