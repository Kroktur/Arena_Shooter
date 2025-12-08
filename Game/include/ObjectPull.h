#pragma once
#include <map>
#include <deque>
#include "Tools/Rtti.h"



template<typename PullType,size_t pullSize>
class ObjectPull
{
public:
	using keyType = std::pair<int, PullType*>;

	template<typename FN,typename... Args>
	static keyType PullValidObject(FN&& fn,Args&&... args)
	{
		if (m_available.empty())
			PullItem<FN,Args...>(std::forward<FN>(fn),std::forward<Args>(args)...);

		auto index = m_available.front();
		m_available.pop_front();
		return keyType{index,m_allNode[index]};
	}

	template<typename FN,typename CD, typename... Args>
	static keyType PullValidObjectWithCondition(FN&& fn,CD&& cd, Args&&... args)
	{
		if (m_available.empty())
			PullItem<FN, Args...>(std::forward<FN>(fn), std::forward<Args>(args)...);


		for (auto it = m_available.begin(); it != m_available.end(); ++it)
		{
			int index = *it;
			if (std::forward<CD>(cd)(m_allNode[index]))
			{
				m_available.erase(it);
				return keyType{ index,m_allNode[index] };
			}
		}

		PullItem<FN, Args...>(std::forward<FN>(fn), std::forward<Args>(args)...);
		auto index = m_available.front();
		m_available.pop_front();
		return keyType{ index,m_allNode[index] };
	}

	static PullType* GetObject(int index)
	{
		if (!m_allNode.contains(index))
			throw std::out_of_range("node not register");
		return m_allNode[index];
	}

	static int GetObjectIndex(PullType* node)
	{
		auto it = std::find_if(
			m_allNode.begin(), m_allNode.end(),
			[node](const auto& pair) { return pair.second == node; }
		);

		if (it == m_allNode.end())
			throw std::out_of_range("node not registered");

		return it->first;
	}

	template<typename FN, typename... Args>
	static void ResetObject(int index,FN&& fn, Args&&... args)
	{
		if (!m_allNode.contains(index))
			throw std::out_of_range("node not register");
		std::forward<FN>(fn)(m_allNode[index], std::forward<Args>(args)...);
		m_available.push_back(index);
	}

	template<typename FN, typename... Args>
	static void ResetObject(PullType* object, FN&& fn, Args&&... args)
	{
		ResetObject<FN,Args...>(GetObjectIndex(object), std::forward<FN>(fn), std::forward<Args>(args)...);
	}

	template<typename FN, typename... Args>
	static void DestroyItem(int index, FN&& fn, Args&&... args)
	{
		if (!m_allNode.contains(index))
			throw std::out_of_range("node not register");
		std::forward<FN>(fn)(m_allNode[index], std::forward<Args>(args)...);
		m_allNode.erase(index);
		m_createPriority.push_back(index);
	}

	template<typename FN, typename... Args>
	static void DestroyItem(PullType* object, FN&& fn, Args&&... args)
	{
		DestroyItem<FN,Args...>(GetObjectIndex(object), std::forward<FN>(fn), std::forward<Args>(args)...);
	}
protected:
	template<typename FN, typename... Args>
	static void PullItem(FN&& fn, Args&&... args)
	{
		for (int i = 0; i < pullSize; ++i)
		{
			if (m_createPriority.empty())
			{
				int index = KT::RTTI::GetInstanceId<PullType>();
				m_available.push_back(index);
				m_allNode[index] = std::forward<FN>(fn)(std::forward<Args>(args)...);
			}
			else
			{
				auto index = m_createPriority.front();
				m_createPriority.pop_front();
				m_available.push_front(index);
				m_allNode[index] = std::forward<FN>(fn)(std::forward<Args>(args)...);
			}
		}
	}
	static std::map<int, PullType*> m_allNode;
	static std::deque<int> m_available;
	static std::deque<int> m_createPriority;
};


template<typename PullType, size_t pullSize>
std::map<int, PullType*> ObjectPull<PullType,pullSize>::m_allNode = {};
template<typename PullType, size_t pullSize>
std::deque<int> ObjectPull<PullType, pullSize>::m_available = {};
template<typename PullType, size_t pullSize>
std::deque<int> ObjectPull<PullType, pullSize>::m_createPriority = {};
