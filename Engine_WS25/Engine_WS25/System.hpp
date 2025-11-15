#pragma once

#include "ComponentType.hpp"

struct ECSView;

class System
{
public:
	System() = default;
	virtual ~System() = default;

	void virtual update(float dT) { return; }
	bool checkView();

protected:
	std::shared_ptr<ECSView> m_view;
	std::vector<ComponentType> m_requiredComponents;
};

