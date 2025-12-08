#pragma once
#include <map>
#include "queue"
#include "Tools/Rtti.h"



template<typename PullType,size_t pullSize>
class ObjectPull
{
public:
	virtual ~ObjectPull() = default;
	int GetValidIndex()
	{
		if (m_available.empty())
			PullItem();
		auto index = m_available.front();
		m_available.pop();
		return index;
	}
	PullType* GetItem(int index)
	{
		if (!m_allNode.contains(index))
			throw std::out_of_range("node not register");
		return m_allNode[index];
	}
	int GetItemIndex(PullType* node)
	{
		auto it = std::find_if(
			m_allNode.begin(), m_allNode.end(),
			[node](const auto& pair) { return pair.second == node; }
		);

		if (it == m_allNode.end())
			throw std::out_of_range("node not registered");

		return it->first;
	}
	void ResetItem(int index)
	{
		if (!m_allNode.contains(index))
			throw std::out_of_range("node not register");
		Reset(index);
		m_available.push(index);
	}
	void DestroyItem(int index)
	{
		if (!m_allNode.contains(index))
			throw std::out_of_range("node not register");
		Destroy(m_allNode[index]);
		m_allNode.erase(index);
		m_createPriority.push(index);
	}
protected:
	virtual PullType* Create() = 0;
	virtual void Destroy(PullType*) = 0;
	virtual void Reset(int index) = 0;
	void PullItem()
	{
		if (!m_available.empty())
			throw std::out_of_range("you have item left");
		for (int i = 0; i < pullSize; ++i)
		{
			if (m_createPriority.empty())
			{
				int index = KT::RTTI::GetInstanceId<PullType>();
				m_available.push(index);
				m_allNode[index] = Create();
			}
			else
			{
				auto index = m_createPriority.front();
				m_createPriority.pop();
				m_available.push(index);
				m_allNode[index] = Create();
			}
		}
	}
	std::map<int, PullType*> m_allNode;
	std::queue<int> m_available;
	std::queue<int> m_createPriority;
};



