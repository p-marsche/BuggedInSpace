#include "pch.h"

#include "Registry.hpp"
#include "HealthSystem.hpp"

HealthSystem::HealthSystem()
{
	m_requiredComponents.push_back(ComponentType::Health);
	m_requiredComponents.push_back(ComponentType::Status);
	m_requiredComponents.push_back(ComponentType::Transform);
	m_view = Registry::getInstance().getView(m_requiredComponents);
}

void HealthSystem::update(float dT)
{

}