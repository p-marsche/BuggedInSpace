#pragma once

#include "ComponentType.hpp"

class System
{
public:
	System() = default;
	virtual ~System() = default;

	void virtual update(float dT) { return; }
	//void virtual checkView() = 0;

protected:
	std::vector<ComponentType> m_requiredComponents;
};

