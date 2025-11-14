#pragma once

#include "ComponentType.hpp"

struct ECSView
{
public:
	std::vector<int> m_entities;
	std::unordered_map<ComponentType, std::vector<int>> m_componentVecs;
};