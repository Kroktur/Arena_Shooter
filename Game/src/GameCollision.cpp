#include "GameCollision.h"

void Collision::Resolve(MyPlayer& player, Fox& fox, solver solver)
{
	auto Mesh = player.GetComponent<MeshComponent<IGameObject>>();
	Ogre::SceneNode* playerNode = Mesh->GetNode();
	playerNode->translate(-solver.mvt.x, -solver.mvt.y, -solver.mvt.z);
}

void Collision::Resolve(Fox& fox, MyPlayer& player, solver solver)
{
	auto Mesh = player.GetComponent<MeshComponent<IGameObject>>();
	Ogre::SceneNode* playerNode = Mesh->GetNode();
	playerNode->translate(solver.mvt.x, solver.mvt.y, solver.mvt.z);
}

void Collision::Resolve(MyPlayer& player, MapTile& map, solver solver)
{
	auto Mesh = player.GetComponent<MeshComponent<IGameObject>>();
	Ogre::SceneNode* playerNode = Mesh->GetNode();
	playerNode->translate(-solver.mvt.x, -solver.mvt.y, -solver.mvt.z);
}

void Collision::Resolve(MapTile& map, MyPlayer& player, solver solver)
{
	auto Mesh = player.GetComponent<MeshComponent<IGameObject>>();
	Ogre::SceneNode* playerNode = Mesh->GetNode();
	playerNode->translate(solver.mvt.x, solver.mvt.y, solver.mvt.z);
}

void Collision::Resolve(MapTile& map, Fox& fox, solver solver)
{
	auto Mesh = fox.GetComponent<MeshComponent<IGameObject>>();
	Ogre::SceneNode* playerNode = Mesh->GetNode();
	playerNode->translate(solver.mvt.x, solver.mvt.y, solver.mvt.z);
}

void Collision::Resolve(Fox& fox, MapTile& map, solver solver)
{
	auto Mesh = fox.GetComponent<MeshComponent<IGameObject>>();
	Ogre::SceneNode* playerNode = Mesh->GetNode();
	playerNode->translate(-solver.mvt.x,- solver.mvt.y, -solver.mvt.z);
}

void Collision::Resolve(Wall& wall, Wall& wall2, solver solver)
{
	return;
}

void Collision::Resolve(Fireball& fireBall, Wall& wall2, solver solver)
{
	auto living = fireBall.GetComponent<LivingComponent<IGameObject>>();
	living->EnableDeath();
}

void Collision::Resolve(Fireball& fireBall, Fox& wall2, solver solver)
{
	auto living = fireBall.GetComponent<LivingComponent<IGameObject>>();
	living->EnableDeath();
}

void Collision::Resolve(Fireball& fireBall, MapTile& wall2, solver solver)
{
	auto living = fireBall.GetComponent<LivingComponent<IGameObject>>();
	living->EnableDeath();
}
