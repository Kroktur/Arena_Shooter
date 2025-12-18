#include "MapObject.h"

#include "MyMeshReader.h"

MapTile::MapTile(KT::IComposite<IGameObject, Demo::ArenaShooterGameState>* owner, Ogre::SceneNode* node,
                 Ogre::Item* item) : KT::CompositeCRTP<MapTile, IGameObject, Demo::ArenaShooterGameState>(owner)
{
	auto mesh = AddComponent<MeshComponent<IGameObject>>(node,item);

	
}

void MapTile::Init()
{
	auto meshComp = GetComponent<MeshComponent<IGameObject>>();
	auto AABB = MeshTools::ExtractAABB(meshComp->GetItem());
	auto obb = KT::OBB3DF(AABB.GetPts());
	auto collide = AddComponent<CollisionComponent<IGameObject>>();
	collide->AddObb(obb);
	collide->UpdateGlobalOBB(0, fullTransform2Data(meshComp->GetNode()->_getFullTransformUpdated()));
	collide->SetLayer("Map");
}

void MapTile::Exit()
{
}

void MapTile::update(float deltaTime)
{
}

void MapTile::input()
{
}
