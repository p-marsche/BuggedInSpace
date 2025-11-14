#include "pch.h"

#include "Registry.hpp"
#include "PhysicsSystem.hpp"

PhysicsSystem::PhysicsSystem()
{
	m_requiredComponents.push_back(ComponentType::Physics);
	m_requiredComponents.push_back(ComponentType::Status);
	m_requiredComponents.push_back(ComponentType::Transform);

	m_physicsPtr =
		std::dynamic_pointer_cast<ComponentBlock<PhysicsComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Physics));
	m_statusPtr =
		std::dynamic_pointer_cast<ComponentBlock<StatusComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Status));
	m_transformPtr =
		std::dynamic_pointer_cast<ComponentBlock<TransformComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Transform));

	m_view = Registry::getInstance().getView(m_requiredComponents);
}

void PhysicsSystem::update(float dT)
{

}