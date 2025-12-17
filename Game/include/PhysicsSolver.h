#pragma once
#include <map>
#include <vector>

#include "IGameObject.h"
#include "Math/OBB.h"
#include "Core/CollisionSolver.h"
#include "Core/Composite.h"
#include "Math/AABB.h"
using BaseComponent = KT::IComponent<IGameObject,Demo::ArenaShooterGameState>;

struct SolverInfo
{
    BaseComponent* object = nullptr;
    std::vector<KT::OBB3DF> allBox;
    KT::AABB3DF bigBox;
};

struct SolverResult
{
    BaseComponent* lhsObject = nullptr;
    BaseComponent* rhsObject = nullptr;
    KT::SolverResult<float, 3, KT::Vector3> result;
};

class OgreSolver
{
public:
    static void ADD(BaseComponent* object, const std::vector<KT::OBB3DF>& boxes)
    {
	    auto result = SolverInfo();
		result.object = object;
		result.allBox = boxes;
		result.bigBox = ComputeAllAABB(boxes);
		m_info.push_back(result);
    }
	static void ADDStatic(BaseComponent* object, const std::vector<KT::OBB3DF>& boxes)
	{
		auto result = SolverInfo();
		result.object = object;
		result.allBox = boxes;
		result.bigBox = ComputeAllAABB(boxes);
		m_fixInfo.push_back(result);
	}
    static void Clear()
    {
        m_info.clear();
    }
    static std::vector<SolverResult> Compute()
    {
		std::vector<SolverResult> obbtest;

		for (int i = 0; i < m_info.size(); ++i)
		{
			for (int j = i + 1; j < m_info.size(); ++j)
			{
				if (m_info[i].object->IsInSubTree(m_info[j].object) || m_info[j].object->IsInSubTree(m_info[i].object))
					continue;

				if (KT::CollisionSolver::SolveAABB(m_info[i].bigBox, m_info[j].bigBox).isColliding)
				{

					auto betterCollision = SolveComplex(m_info[i].allBox, m_info[j].allBox);
					if (betterCollision.isColliding)
					{
						SolverResult result;
						result.lhsObject = m_info[i].object;
						result.rhsObject = m_info[j].object;
						result.result = betterCollision;
						obbtest.push_back(result);
					}
				}
			}
			for (int j = 0 ; j < m_fixInfo.size(); ++j)
			{
				if (m_info[i].object->IsInSubTree(m_fixInfo[j].object) || m_fixInfo[j].object->IsInSubTree(m_info[i].object))
					continue;

				if (KT::CollisionSolver::SolveAABB(m_info[i].bigBox, m_fixInfo[j].bigBox).isColliding)
				{
					auto betterCollision = SolveComplex(m_info[i].allBox, m_fixInfo[j].allBox);
					if (betterCollision.isColliding)
					{
						SolverResult result;
						result.lhsObject = m_info[i].object;
						result.rhsObject = m_fixInfo[j].object;
						result.result = betterCollision;
						obbtest.push_back(result);
					}
				}
			}
		}
		return obbtest;
    }
private:
    static KT::AABB3DF ComputeAllAABB(const std::vector<KT::OBB3DF>& obb)
    {
        KT::AABB3DF result = ComputeAABB(obb.front());
        for (auto i = 1 ; i < obb.size() ; ++i)
        {
            result.Merge(ComputeAABB(obb[i]));
		}
		return result;
    }

	    static KT::SolverResult<float, 3, KT::Vector3> SolveComplex(const std::vector<KT::OBB3DF>& lhsObbs, const std::vector<KT::OBB3DF>& RhsObbs)
	    {
	        std::vector<KT::SolverResult<float, 3, KT::Vector3>> m_potential;
	        for (auto& lhsObb : lhsObbs)
	        {
	            for (auto& rhsObb : RhsObbs)
	            {
	                auto result = SolveComplex(lhsObb, rhsObb);
	                if (result.isColliding)
	                    m_potential.push_back(result);
	            }
	        }
	        KT::SolverResult<float, 3, KT::Vector3> finalResult;
	        if (m_potential.empty())
	        {
		        finalResult.isColliding = false;
				return finalResult;
	        }
	        float depthTotal = 0;
			float maxDepth = 0;
	        for (auto& result : m_potential)
	        {
				depthTotal += result.depth;
	            maxDepth = KT::Math::Max(maxDepth, result.depth);
	        }
			KT::Vector3F normalTotal = { 0,0,0 };
	        for (auto& result : m_potential)
	        {
	            normalTotal += result.normal * (result.depth / depthTotal);
	        }
		
			finalResult.depth = maxDepth;
			finalResult.normal = normalTotal.Normalize();
	        finalResult.mvt = finalResult.normal * finalResult.depth;
			finalResult.isColliding = true;
			return finalResult;
	    }

    static KT::SolverResult<float,3,KT::Vector3> SolveComplex(const KT::OBB3DF& lhs, const KT::OBB3DF& rhs)
    {
        return  KT::CollisionSolver::SolveOBB<float, 3, KT::Vector3>(lhs, rhs);
    }

    static KT::AABB3DF ComputeAABB(const KT::OBB3DF& obb)
    {
        // Contribution of axis X scaled
        KT::Vector3F ax = obb.axes[0] * obb.halfSize.x;
        KT::Vector3F  ay = obb.axes[1] * obb.halfSize.y;
        KT::Vector3F  az = obb.axes[2] * obb.halfSize.z;

        // Abs to get extents
        KT::Vector3F  ex = { KT::Math::AbsoluteValue(ax.x), KT::Math::AbsoluteValue(ax.y),KT::Math::AbsoluteValue(ax.z) };
        KT::Vector3F  ey = { KT::Math::AbsoluteValue(ay.x), KT::Math::AbsoluteValue(ay.y), KT::Math::AbsoluteValue(ay.z) };
        KT::Vector3F  ez = { KT::Math::AbsoluteValue(az.x), KT::Math::AbsoluteValue(az.y), KT::Math::AbsoluteValue(az.z) };

        KT::Vector3F  extent = ex + ey +ez;

        KT::AABB3DF box;
        box.Amin = obb.center - extent;
        box.Amax = obb.center + extent;

        return box;
    }
    static std::vector<SolverInfo> m_info;
	static std::vector<SolverInfo> m_fixInfo;
};
inline std::vector<SolverInfo> OgreSolver::m_info = {};
inline std::vector<SolverInfo> OgreSolver::m_fixInfo = {};