#include <cstdio>
#include <vector>
#include <iostream>
#include <filesystem>
#include <fstream>
#include "ofbx.h"
#include "fbxLoader.h"
#include "OgreItem.h"
#include "Ogre.h"
#include "GraphicsSystem.h"
#include "OgreManualObject2.h"
#include "OgreHlmsPbs.h"
#include "OgreHlmsPbsDatablock.h"

Ogre::Item* loadMap::createItemFromFBX(Ogre::SceneManager* sceneMgr, const ofbx::Mesh* mesh, int meshIdx)
{
	const ofbx::Geometry* geometry = mesh->getGeometry();
	if (!geometry)
		return nullptr;

	const ofbx::GeometryData& data = geometry->getGeometryData();

	ofbx::Vec3Attributes positions = data.getPositions();
	ofbx::Vec3Attributes normals = data.getNormals();
	ofbx::Vec2Attributes uvs = data.getUVs();

	if (positions.count == 0)
		return nullptr;

	Ogre::ManualObject* manualGO = sceneMgr->createManualObject();
	manualGO->begin("Default", Ogre::OT_TRIANGLE_LIST);
	int partitionCount = data.getPartitionCount();

	if (partitionCount > 0)
	{
		int vertexCount = 0;

		for (int partition = 0; partition < partitionCount; partition++)
		{
			ofbx::GeometryPartition geometryP = data.getPartition(partition);
			for (int i = 0; i < geometryP.polygon_count; i++)
			{
				const auto& polygon = geometryP.polygons[i];
				int polygonStart = vertexCount;

				for (int j = 0; j < polygon.vertex_count; j++)
				{
					int idx = polygon.from_vertex + j;
					ofbx::Vec3 position = positions.get(idx);
					manualGO->position(position.x, position.y, position.z);

					if (normals.count > idx)
					{
						ofbx::Vec3 normal = normals.get(idx);
						manualGO->normal(normal.x, normal.y, normal.z);
					}
					if (uvs.count > idx)
					{
						ofbx::Vec2 uv = uvs.get(idx);
						manualGO->textureCoord(uv.x, 1.0f - uv.y);
					}
					vertexCount++;
				}

				for (int j = 1; j < polygon.vertex_count - 1; j++)
				{
					manualGO->triangle(polygonStart, polygonStart + j, polygonStart + j + 1);
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < positions.count; i++)
		{
			ofbx::Vec3 position = positions.get(i);
			manualGO->position(position.x, position.y, position.z);

			if (normals.count > i)
			{
				ofbx::Vec3 normal = normals.get(i);
				manualGO->normal(normal.x, normal.y, normal.z);
			}
			if (uvs.count > i)
			{
				ofbx::Vec2 uv = uvs.get(i);
				manualGO->textureCoord(uv.x, 1.0f - uv.y);
			}
		}

		for (int i = 0; i < positions.count; i += 3)
		{
			if (i + 2 < positions.count)
				manualGO->triangle(i, i + 1, i + 2);
		}
	}

	manualGO->end();

	Ogre::String meshName = "FBXMesh_" + Ogre::StringConverter::toString(meshIdx) +
		"_" + Ogre::StringConverter::toString(rand());
	manualGO->convertToMesh(meshName);

	Ogre::Item* item = sceneMgr->createItem(meshName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::SCENE_DYNAMIC);

	sceneMgr->destroyManualObject(manualGO);

	return item;
}

Ogre::Item* loadMap::getMaterialFromFBX(Ogre::Item* item, const ofbx::Mesh* mesh, int meshIdx, Demo::GraphicsSystem *mgraphsys)
{
	if (!mesh)
		throw;
	const ofbx::Material* material = mesh->getMaterial(0);
	if (!material)
		return item;

	Ogre::HlmsManager* hlmsManager = mgraphsys->getRoot()->getHlmsManager();
	Ogre::HlmsPbs* hlmsPbs = static_cast<Ogre::HlmsPbs*>(hlmsManager->getHlms(Ogre::HLMS_PBS));

	Ogre::String datablockName = "FBXMat_" + Ogre::StringConverter::toString(meshIdx);
	Ogre::HlmsPbsDatablock* datablock = static_cast<Ogre::HlmsPbsDatablock*>(
		hlmsPbs->createDatablock(datablockName,
			datablockName, Ogre::HlmsMacroblock(),
			Ogre::HlmsBlendblock(), Ogre::HlmsParamVec()));

	ofbx::Color diffuseColor = material->getDiffuseColor();
	datablock->setDiffuse(Ogre::Vector3(diffuseColor.r, diffuseColor.g, diffuseColor.b));

	auto shininess = material->getShininess();
	auto roughness = 1.0f - (shininess / 100.0f);
	datablock->setRoughness(roughness);

	const ofbx::Texture* diffuseTexture = material->getTexture(ofbx::Texture::DIFFUSE);
	if (diffuseTexture)
	{
		ofbx::DataView pathView = diffuseTexture->getRelativeFileName();
		if (pathView.begin && pathView.end > pathView.begin)
		{
			std::string fullPath(pathView.begin, pathView.end);
			size_t lastSlash = fullPath.find_last_of("/\\");
			std::string textureFilename = (lastSlash != std::string::npos) ? fullPath.substr(lastSlash + 1) : fullPath;

			try
			{
				datablock->setTexture(Ogre::PBSM_DIFFUSE, textureFilename);
			}
			catch (...)
			{

			}
		}
	}
	const ofbx::Texture* normalTexture = material->getTexture(ofbx::Texture::NORMAL);
	if (normalTexture)
	{
		ofbx::DataView pathView = normalTexture->getRelativeFileName();
		if (pathView.begin && pathView.end > pathView.begin)
		{
			std::string fullPath(pathView.begin, pathView.end);
			size_t lastSlash = fullPath.find_last_of("/\\");
			std::string textureFilename = (lastSlash != std::string::npos) ? fullPath.substr(lastSlash + 1) : fullPath;

			try
			{
				datablock->setTexture(Ogre::PBSM_NORMAL, textureFilename);
			}
			catch (...)
			{
			}
		}
	}
	const ofbx::Texture* emissiveTexture = material->getTexture(ofbx::Texture::EMISSIVE);
	if (emissiveTexture)
	{
		ofbx::DataView pathView = emissiveTexture->getRelativeFileName();
		if (pathView.begin && pathView.end > pathView.begin)
		{
			std::string fullPath(pathView.begin, pathView.end);
			size_t lastSlash = fullPath.find_last_of("/\\");
			std::string textureFilename = (lastSlash != std::string::npos) ? fullPath.substr(lastSlash + 1) : fullPath;

			try
			{
				datablock->setTexture(Ogre::PBSM_EMISSIVE, textureFilename);
			}
			catch (...)
			{
			}
		}
	}

	item->setDatablock(datablock);
	return item;
}

std::vector<uint8_t> loadMap::loadFile(const char* path)
{
	// Load file into memory as byte buffer
	std::ifstream file(path, std::ios::binary);

	if (!file)
		return std::vector<uint8_t>();

	file.seekg(0, std::ios::end);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<uint8_t> buffer(size);
	file.read(reinterpret_cast<char*>(buffer.data()), size);

	return buffer;
}

void loadMap::extractTransform(const ofbx::DMatrix& matrix, Ogre::Vector3& position, Ogre::Quaternion& rotation,
	Ogre::Vector3& scale)
{
	// Extract position from last column
	position.x = static_cast<float>(matrix.m[12]);
	position.y = static_cast<float>(matrix.m[13]);
	position.z = static_cast<float>(matrix.m[14]);

	// Extract basis vectors from first 3 columns
	Ogre::Vector3 right(matrix.m[0], matrix.m[1], matrix.m[2]);
	Ogre::Vector3 up(matrix.m[4], matrix.m[5], matrix.m[6]);
	Ogre::Vector3 forward(matrix.m[8], matrix.m[9], matrix.m[10]);

	// Scale is the length of each basis vector
	scale.x = right.length();
	scale.y = up.length();
	scale.z = forward.length();

	// Normalize basis vectors to get pure rotation
	if (scale.x > 0.0001f)
		right /= scale.x;
	if (scale.y > 0.0001f)
		up /= scale.y;
	if (scale.z > 0.0001f)
		forward /= scale.z;

	// Build rotation matrix from normalized basis vectors
	Ogre::Matrix3 rotationMatrix;
	rotationMatrix[0][0] = right.x; rotationMatrix[0][1] = up.x; rotationMatrix[0][2] = forward.x;
	rotationMatrix[1][0] = right.y; rotationMatrix[1][1] = up.y; rotationMatrix[1][2] = forward.y;
	rotationMatrix[2][0] = right.z; rotationMatrix[2][1] = up.z; rotationMatrix[2][2] = forward.z;

	// Convert rotation matrix to quaternion
	rotation.FromRotationMatrix(rotationMatrix);
}