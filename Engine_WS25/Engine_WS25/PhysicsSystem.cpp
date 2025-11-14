#include "pch.h"

#include "Registry.hpp"
#include "PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem()
{
	m_requiredComponents.push_back(ComponentType::Physics);
	m_requiredComponents.push_back(ComponentType::Status);
	m_requiredComponents.push_back(ComponentType::Transform);
	m_view = Registry::getInstance().getView(m_requiredComponents);
}

void PhysicsSystem::update(float dT)