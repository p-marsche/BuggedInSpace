#include "pch.h"

#include "Registry.hpp"
#include "System.hpp"

bool System::checkView()
{
	bool areBlocksDirty = false;
	for (auto& type : m_requiredComponents)
	{
		auto flagPtr = Registry::getInstance().m_blockIsDirty.find(type);
		if (flagPtr == Registry::getInstance().m_blockIsDirty.end())
			continue;

		areBlocksDirty = areBlocksDirty || flagPtr->second;
	}

	if (areBlocksDirty)
		m_view = Registry::getInstance().getView(m_requiredComponents);

	return areBlocksDirty;
}