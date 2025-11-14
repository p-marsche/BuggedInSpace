#pragma once

struct IComponent
{
public:
	IComponent(int entity_ID);
	virtual ~IComponent() = default;

	int m_entityID;
};
