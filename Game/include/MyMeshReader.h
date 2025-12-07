#pragma once
#include <iostream>

#include "OgreItem.h"
#include "OgreMesh2.h"
#include "OgreSubMesh2.h"
#include "OgreItem.h"
#include "OgreSceneNode.h"
#include "OgreHardwareVertexBuffer.h"
#include "OgreVector3.h"
#include "OgreMatrix4.h"
#include "Tools/Chrono.h"
#include "Vao/OgreAsyncTicket.h"
#include <OgreMesh.h>
#include <OgreSubMesh.h>
#include <OgreHardwareBuffer.h>
#include <OgreVector3.h>
#include <OgreQuaternion.h>
#include "OgreRoot.h"
#include "Math/MyMath.h"
#include "Math/Vector3.h"



struct MeshTools
{
	static Ogre::MeshPtr ExtractMesh(const Ogre::Item* item) 
	{
		// no item
		if (!item)
			return nullptr;
		// return mesh
		return item->getMesh();
	}
	static Ogre::VertexBufferPackedVec GetVertexBuffer(Ogre::SubMesh* subMesh)
	{
		// get first mVao
		Ogre::VertexArrayObjectArray vaos = subMesh->mVao[Ogre::VpNormal];
		// means no vertices return emtpy vertexBuffer
		if (vaos.empty())
			return {};

		// first vao has always position
		Ogre::VertexArrayObject* vao = vaos[0];

		//get vertex buffer
		return vao->getVertexBuffers();
	}

	static std::vector<KT::Vector3F> GetPosition(Ogre::VertexBufferPacked* vertexBuffer)
	{
        std::vector<KT::Vector3F> positions;
        const void* bufferData = nullptr;

        if (vertexBuffer->getShadowCopy())
        {
            bufferData = vertexBuffer->getShadowCopy();
        }
        else
        {
            // map
            bufferData = vertexBuffer->map(0, vertexBuffer->getNumElements());
        }

        if (!bufferData)
            return positions;

        const Ogre::VertexElement2Vec& vertexElements = vertexBuffer->getVertexElements();

        size_t positionOffset = 0;
        bool hasPosition = false;



        // verify de bite where position is 
        for (const auto& element : vertexElements)
        {
            if (element.mSemantic == Ogre::VES_POSITION)
            {
                hasPosition = true;
                break;
            }
            positionOffset += getVertexElementTypeSize(element.mType);
        }

        // contain no position return 
        if (!hasPosition)
        {
            // clean if map
            if (!vertexBuffer->getShadowCopy())
                vertexBuffer->unmap(Ogre::UO_KEEP_PERSISTENT);
            return positions;
        }

        size_t vertexCount = vertexBuffer->getNumElements();
        size_t bytesPerVertex = vertexBuffer->getBytesPerElement();

        for (size_t vertexIdx = 0; vertexIdx < vertexCount; ++vertexIdx)
        {
            const char* vertexData = static_cast<const char*>(bufferData) +
                (vertexIdx * bytesPerVertex) +
                positionOffset;

            const float* positionData = reinterpret_cast<const float*>(vertexData);

            KT::Vector3F position(
                positionData[0] ,
                positionData[1] ,
                positionData[2] 
            );


            positions.push_back(position);
        }

        // clean if map
        if (!vertexBuffer->getShadowCopy())
            vertexBuffer->unmap(Ogre::UO_KEEP_PERSISTENT);

        return positions;
	}


    static std::vector<KT::Vector3F> GetAllPosition(const Ogre::Item* item)
	{
        std::vector<KT::Vector3F> positions;
        auto mesh = MeshTools::ExtractMesh(item);
        for (auto i = 0; i < mesh->getNumSubMeshes(); ++i)
        {
            auto subMesh = mesh->getSubMesh(i);
            auto vertexBuffers = MeshTools::GetVertexBuffer(subMesh);
            for (int j = 0; j < vertexBuffers.size(); ++j)
            {
                auto toAdd = MeshTools::GetPosition(vertexBuffers[j]);
                positions.insert(positions.end(), toAdd.begin(), toAdd.end());
            }
        }
        return positions;
	}

private:
    static size_t getVertexElementTypeSize(Ogre::VertexElementType type)
    {
        switch (type)
        {
        case Ogre::VET_FLOAT1:      return sizeof(float);
        case Ogre::VET_FLOAT2:      return sizeof(float) * 2;
        case Ogre::VET_FLOAT3:      return sizeof(float) * 3;
        case Ogre::VET_FLOAT4:      return sizeof(float) * 4;
        case Ogre::VET_SHORT2:      return sizeof(short) * 2;
        case Ogre::VET_SHORT4:      return sizeof(short) * 4;
        case Ogre::VET_UBYTE4:      return sizeof(unsigned char) * 4;
        case Ogre::VET_BYTE4:       return sizeof(char) * 4;
        case Ogre::VET_USHORT2:     return sizeof(unsigned short) * 2;
        case Ogre::VET_USHORT4:     return sizeof(unsigned short) * 4;
        case Ogre::VET_INT1:        return sizeof(int);
        case Ogre::VET_INT2:        return sizeof(int) * 2;
        case Ogre::VET_INT3:        return sizeof(int) * 3;
        case Ogre::VET_INT4:        return sizeof(int) * 4;
        case Ogre::VET_UINT1:       return sizeof(unsigned int);
        case Ogre::VET_UINT2:       return sizeof(unsigned int) * 2;
        case Ogre::VET_UINT3:       return sizeof(unsigned int) * 3;
        case Ogre::VET_UINT4:       return sizeof(unsigned int) * 4;
        case Ogre::VET_DOUBLE1:     return sizeof(double);
        case Ogre::VET_DOUBLE2:     return sizeof(double) * 2;
        case Ogre::VET_DOUBLE3:     return sizeof(double) * 3;
        case Ogre::VET_DOUBLE4:     return sizeof(double) * 4;
        case Ogre::VET_HALF2:       return sizeof(uint16_t) * 2;
        case Ogre::VET_HALF4:       return sizeof(uint16_t) * 4;
        case Ogre::VET_UBYTE4_NORM: return sizeof(unsigned char) * 4;
        case Ogre::VET_USHORT2_NORM: return sizeof(unsigned short) * 2;
        case Ogre::VET_USHORT4_NORM: return sizeof(unsigned short) * 4;
        default: return 0;
        }
    }

};
