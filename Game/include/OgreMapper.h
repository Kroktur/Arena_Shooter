#pragma once
#include <OgreItem.h>

#include "MyMeshReader.h"
#include "Core/CollisionMapper.h"

namespace Priv
{
	inline KT::OBB3DF GetOBBFromMesh(Ogre::Item* item)
	{
		auto pts = MeshTools::GetAllPosition(item);
		return KT::OBB3DF(pts);
	}
}

using OgreMapper = KT::OBB3DFMapper<std::string, Ogre::Item, Priv::GetOBBFromMesh>;