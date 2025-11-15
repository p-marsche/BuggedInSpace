#pragma once

#include "ComponentType.hpp"

struct ECSView
{
public:
	std::vector<int> m_entities; // = std::vector<int>();
	std::unordered_map<ComponentType, std::vector<int>> m_componentVecs; // =
		//std::unordered_map<.....>();
};