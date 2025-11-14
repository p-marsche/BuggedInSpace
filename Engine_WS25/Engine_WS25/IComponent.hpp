#pragma once

#include "ComponentType.hpp"

struct IComponent
{
public:
	IComponent(int entity_ID);
	virtual ~IComponent() = default;

	virtual ComponentType GetType() { return ComponentType::LAST; }

	int m_entityID;
};
