#pragma once
#include "Fox.h"
#include "MyPlayer.h"
using solver = KT::SolverResult<float, 3, KT::Vector3>;
namespace Collision
{
	void Resolve(MyPlayer& player, Fox& fox, solver solver);
	void Resolve( Fox& fox,MyPlayer& player,solver solver);

}
