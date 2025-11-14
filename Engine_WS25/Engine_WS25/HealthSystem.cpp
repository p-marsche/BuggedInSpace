#include "pch.h"

#include "Registry.hpp"
#include "HealthSystem.hpp"

HealthSystem::HealthSystem()
{
	m_requiredComponents.push_back(ComponentType::Health);
	m_requiredComponents.push_back(ComponentType::Status);
	m_requiredComponents.push_back(ComponentType::Transform);

	m_healthPtr =
		std::dynamic_pointer_cast<ComponentBlock<HealthComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Health));
	m_statusPtr =
		std::dynamic_pointer_cast<ComponentBlock<StatusComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Status));
	m_transformPtr =
		std::dynamic_pointer_cast<ComponentBlock<TransformComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Transform));

	m_view = Registry::getInstance().getView(m_requiredComponents);
}

void HealthSystem::update(float dT)
{

}