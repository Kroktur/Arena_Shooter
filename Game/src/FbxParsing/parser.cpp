#include <cstdio>
#include <vector>
#include <iostream>
#include "ofbx.h"
#include "fbxLoader.h"
#include "OgreItem.h"
#include "Ogre.h"
#include "GraphicsSystem.h"
#include "OgreManualObject2.h"

std::vector<const ofbx::Mesh*> parser() 
{
	const char* fbxFile = "../../tree.fbx";
    FILE* f = fopen(fbxFile, "rb");

    if (!f) {
        std::cerr << "Failed to open FBX: " << fbxFile << "\n";
    }
    fseek(f, 0, SEEK_END);
    size_t size = ftell(f);
    rewind(f);
    if (size <= 0) { 
        fclose(f); std::cerr << "FBX file empty\n";
    }
    std::vector<ofbx::u8> data(size);
    size_t read = fread(data.data(), 1, size, f);
    fclose(f);
    if (read != size) {
		std::cerr << "Failed to read FBX\n";
    }
    ofbx::IScene* scene = ofbx::load(data.data(), (ofbx::usize)size, static_cast<ofbx::u16>(ofbx::LoadFlags::NONE), nullptr, nullptr);
    if (!scene) {
        std::cerr << "Failed to load FBX: " << (ofbx::getError() ? ofbx::getError() : "(no error)") << "\n";
    }
    size_t meshCount = (size_t)scene->getMeshCount();
	std::vector<const ofbx::Mesh*> mesh;
	for (int i = 0; i < meshCount; ++i) {
		mesh.push_back(scene->getMesh(i));
	}
    return mesh;
}

Ogre::Item* Demo::createItemFromFBX(Ogre::SceneManager* sceneMgr, const ofbx::Mesh* mesh, int meshIdx)
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
			for (int i = 0; i < geometryP.polygon_count; i++) {
				const auto& polygon = geometryP.polygons[i];
				int polygonStart = vertexCount;
				for (int j = 0; j < polygon.vertex_count; j++) {
					int idx = polygon.from_vertex + j;
					ofbx::Vec3 position = positions.get(idx);
					manualGO->position(position.x, position.y, position.z);
					if (normals.count > idx) {
						ofbx::Vec3 normal = normals.get(idx);
						manualGO->normal(normal.x, normal.y, normal.z);
					}
					if (uvs.count > idx) {
						ofbx::Vec2 uv = uvs.get(idx);
						manualGO->textureCoord(uv.x, 1.0f - uv.y);
					}
					vertexCount++;
				}
				for (int j = 1; j < polygon.vertex_count - 1; j++) {
					manualGO->triangle(polygonStart, polygonStart + j, polygonStart + j + 1);
				}
			}
		}
	} else {
		for (int i = 0; i < positions.count; i++) {
			ofbx::Vec3 position = positions.get(i);
			manualGO->position(position.x, position.y, position.z);
			if (normals.count > i) {
				ofbx::Vec3 normal = normals.get(i);
				manualGO->normal(normal.x, normal.y, normal.z);
			}
			if (uvs.count > i) {
				ofbx::Vec2 uv = uvs.get(i);
				manualGO->textureCoord(uv.x, 1.0f - uv.y);
			}
		}
		for (int i = 0; i < positions.count; i += 3) {
			if (i + 2 < positions.count)
				manualGO->triangle(i, i + 1, i + 2);
		}
	}
	manualGO->end();
	Ogre::String meshName = "FBXMesh_" + Ogre::StringConverter::toString(meshIdx) +
		"_" + Ogre::StringConverter::toString(rand());
	manualGO->convertToMesh(meshName);
	Ogre::Item* item = sceneMgr->createItem(meshName, Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::SCENE_DYNAMIC);
	sceneMgr->destroyManualObject(manualGO);
	return item;
}
