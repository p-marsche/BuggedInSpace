#pragma once

#include "pch.h"

#include "IComponent.hpp"

struct IComponentBlock
{
public:
	IComponentBlock(int reserveCount) { m_entities.reserve(reserveCount); }
	virtual ~IComponentBlock() = default;

	virtual void remove(int ID) { return; }

	std::vector<int> m_entities; // storing entitiy-IDs
	std::unordered_map<int, int> m_entityToIndex; // key = entityID, value = index
};


template <typename T, typename = std::enable_if_t < std::is_base_of_v<IComponent, T> > >
struct ComponentBlock
	: IComponentBlock
{
public:
	ComponentBlock(int reserveCount)
		: IComponentBlock(reserveCount)
	{
		m_components.reserve(reserveCount);
	}

	// swap & pop, to keep order intact as much as possible upon deletion
	void remove(int ID) override
	{
		if (m_entityToIndex.find(ID) == m_entityToIndex.end()) { return; }

		int index = m_entityToIndex[ID];
		m_components[index] = std::move(m_components.back());
		m_components.pop_back();
		m_entities[index] = std::move(m_entities.back());
		m_entities.pop_back();

		int changedID = m_entities[index];
		m_entityToIndex.at(changedID) = index;
		m_entityToIndex.erase(ID);
	}

	std::vector<T> m_components;
};

