#pragma once
#include "Fox.h"
#include "MapObject.h"
#include "MyPlayer.h"
#include "Wall.h"
using solver = KT::SolverResult<float, 3, KT::Vector3>;
namespace Collision
{
	void Resolve(MyPlayer& player, Fox& fox, solver solver);
	void Resolve( Fox& fox,MyPlayer& player,solver solver);

	void Resolve(MyPlayer& player, MapTile& fox, solver solver);
	void Resolve(MapTile& fox, MyPlayer& player, solver solver);

	void Resolve(MapTile& player, Fox& fox, solver solver);
	void Resolve(Fox& fox, MapTile& player, solver solver);

	void Resolve(Wall& wall, Wall& wall2, solver solver);

}
