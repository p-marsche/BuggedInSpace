#pragma once

#include "pch.h"

#include "IComponent.hpp"

struct IComponentBlock
{
public:
	IComponentBlock(int reserveCount)
	{
		m_entities.reserve(reserveCount);
	}

	virtual ~IComponentBlock() = default;

	std::vector<int> m_entities; // storing entitiy-IDs
	std::unordered_map<int, int> m_entityToIndex;
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

	std::vector<T> m_components;
};

