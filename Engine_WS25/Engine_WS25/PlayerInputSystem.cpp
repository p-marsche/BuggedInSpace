#include "pch.h"

#include "ComponentType.hpp"
#include "Registry.hpp"
#include "PlayerInputSystem.hpp"

PlayerInputSystem::PlayerInputSystem()
{
	m_requiredComponents.push_back(ComponentType::Physics);
	m_requiredComponents.push_back(ComponentType::PlayerInput);
	m_requiredComponents.push_back(ComponentType::Transform);

	m_physicsPtr =
		std::dynamic_pointer_cast<ComponentBlock<PhysicsComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Physics));
	m_inputPtr =
		std::dynamic_pointer_cast<ComponentBlock<PlayerInputComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::PlayerInput));
	m_transformPtr =
		std::dynamic_pointer_cast<ComponentBlock<TransformComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Transform));

	m_view = Registry::getInstance().getView(m_requiredComponents);
}

void PlayerInputSystem::update(float dT)
{
	for (int index : m_view->m_componentVecs.at(ComponentType::PlayerInput))
	{
		
	}
}