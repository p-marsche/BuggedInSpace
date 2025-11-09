#pragma once

#include "ComponentTypeEnum.hpp"

class IComponent
{
public:
	IComponent(ComponentType compType);
	virtual ~IComponent() = default;
	int getID() const { return m_ID; }
	void virtual update(float deltaTime) { return; }

private:
	static int s_nextID;

	int m_ID;
	ComponentType m_compType;
};
