#pragma once
#include <OgreMatrix4.h>
#include "Math/OBB.h"

struct TransformOBBData
{
	KT::Matrix<float, 4> scale;
	KT::Matrix<float, 4> rotation;
	KT::Matrix<float, 4> transform;
};
static TransformOBBData fullTransform2Data(const Ogre::Matrix4& m)
{
	TransformOBBData result;
	// traslation
	result.transform = KT::Matrix<float, 4>::Identity();
	result.transform.SetCell(0, 3, m[0][3]);
	result.transform.SetCell(1, 3, m[1][3]);
	result.transform.SetCell(2, 3, m[2][3]);
	// scale
	KT::Vector3F scale;
	scale.x = KT::Vector3F(m[0][0], m[1][0], m[2][0]).Length();
	scale.y = KT::Vector3F(m[0][1], m[1][1], m[2][1]).Length();
	scale.z = KT::Vector3F(m[0][2], m[1][2], m[2][2]).Length();

	result.scale = KT::Matrix<float, 4>::Identity();
	result.scale.SetCell(0, 0, scale.x);
	result.scale.SetCell(1, 1, scale.y);
	result.scale.SetCell(2, 2, scale.z);
	// rotation

	result.rotation = KT::Matrix<float, 4>::Identity();

	result.rotation.SetCell(0, 0, m[0][0] / scale.x);
	result.rotation.SetCell(0, 1, m[0][1] / scale.y);
	result.rotation.SetCell(0, 2, m[0][2] / scale.z);

	result.rotation.SetCell(1, 0, m[1][0] / scale.x);
	result.rotation.SetCell(1, 1, m[1][1] / scale.y);
	result.rotation.SetCell(1, 2, m[1][2] / scale.z);

	result.rotation.SetCell(2, 0, m[2][0] / scale.x);
	result.rotation.SetCell(2, 1, m[2][1] / scale.y);
	result.rotation.SetCell(2, 2, m[2][2] / scale.z);

	return result;
}

class TransformOBB
{
public:
	static KT::OBB3DF ApplyTransform(const KT::OBB3DF& obbToUse, TransformOBBData transformData)
	{
		auto obb = obbToUse;
		obb = ScaleTransform(obb, transformData.scale);
		obb = RotateTransform(obb, transformData.rotation);
		obb = TranslateTransform(obb, transformData.transform);
		return obb;
	}
private:
	static KT::OBB3DF ScaleTransform(const KT::OBB3DF& obbToUse, KT::Matrix<float,4> transformScale)
	{
		auto obb = obbToUse;
		KT::VectorND<float,4> centerHomogeneous{ obb.center.x, obb.center.y,obb.center.z,1.0f };
		KT::VectorND<float,4> transformedCenter = transformScale.MatrixProduct(centerHomogeneous);
		obb.center.x = transformedCenter[0];
		obb.center.y = transformedCenter[1];
		obb.center.z = transformedCenter[2];

		obb.halfSize.x *= transformScale.GetCell(0,0);
		obb.halfSize.y  *= transformScale.GetCell(1, 1);
		obb.halfSize.z *= transformScale.GetCell(2, 2);
		return  obb;
	}
	static KT::OBB3DF RotateTransform(const KT::OBB3DF& obbToUse, KT::Matrix<float, 4> transformRotate)
	{
		auto obb = obbToUse;
		KT::VectorND<float, 4> centerHomogeneous{ obb.center.x, obb.center.y,obb.center.z,1.0f };
		KT::VectorND<float, 4> transformedCenter = transformRotate.MatrixProduct(centerHomogeneous);
		obb.center.x = transformedCenter[0];
		obb.center.y = transformedCenter[1];
		obb.center.z = transformedCenter[2];

		for (int i = 0; i < 3; ++i) {
			KT::VectorND<float, 4> axeHomogenous{ obb.axes[i].x, obb.axes[i].y,obb.axes[i].z, 0.f };
			KT::VectorND<float, 4> transformedAxe = transformRotate.MatrixProduct(axeHomogenous);
			obb.axes[i].x = transformedAxe[0];
			obb.axes[i].y = transformedAxe[1];
			obb.axes[i].z = transformedAxe[2];
			obb.axes[i].SelfNormalize();
		}
		return obb;
	}
	static KT::OBB3DF TranslateTransform(const KT::OBB3DF& obbToUse, KT::Matrix<float, 4> transformTranslate)
	{
		auto obb = obbToUse;
		KT::VectorND<float, 4> centerHomogeneous{ obb.center.x, obb.center.y, obb.center.z,1.0f };
		KT::VectorND<float, 4> transformedCenter = transformTranslate.MatrixProduct(centerHomogeneous);
		obb.center.x = transformedCenter[0];
		obb.center.y = transformedCenter[1];
		obb.center.z = transformedCenter[2];
		return obb;
	}
};
