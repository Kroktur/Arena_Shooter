#pragma once

#include <OgreCamera.h>
#include <OgreVector3.h>
#include <SDL_events.h>

#include "GraphicsSystem.h"

class MyCamera
{
public:
	explicit MyCamera(Demo::GraphicsSystem* graphicsSystem, bool useSceneNode = false);
	~MyCamera() = default;

	void update(const float& dt);

	// --- getters ---
	Ogre::Camera* getCamera() const;

	// --- setters ---
	void setTarget(Ogre::SceneNode* target);

	// --- input ---
	void onMouseMoved(const SDL_Event& arg);
	bool keyPressed(const SDL_KeyboardEvent& arg);  // Returns true if we've handled the event
	bool keyReleased(const SDL_KeyboardEvent& arg); // Returns true if we've handled the event
	void Input();
private:
	Ogre::Camera* m_camera;
	Ogre::SceneNode* m_camNode; // Node to which the camera is attached

	// --- spring system ---
	Ogre::Vector3 m_targetPosition;
	Ogre::Vector3 m_velocity; // speed memory (for the overshoot)

	// FPS camera control
	float m_cameraYaw;
	float m_cameraPitch;

	// --- booleans ---
	bool m_useSceneNode;
	bool m_speedModifier;
	bool m_ZQSD[4];
	bool m_directionalCross[4];

	// need our own graphics system pointer - TDL
	Demo::GraphicsSystem* m_graphicsSystem;

	Ogre::SceneNode* m_target = nullptr;

public:
	float m_cameraBaseSpeed;
	float m_cameraSpeedBoost;
};