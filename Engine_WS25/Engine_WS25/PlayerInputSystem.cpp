#include "pch.h"

#include "ComponentType.hpp"
#include "InputManager.hpp"
#include "PlayerInputSystem.hpp"
#include "Registry.hpp"

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
	checkView();

	for (unsigned int i = 0; i < m_view->m_entities.size(); i++)
	{
		int iIndex = m_view->m_componentVecs.at(ComponentType::PlayerInput)[i];
		int pIndex = m_view->m_componentVecs.at(ComponentType::Physics)[i];
		int tIndex = m_view->m_componentVecs.at(ComponentType::Transform)[i];

		sf::Keyboard::Key leftKey =
			m_inputPtr->m_components[iIndex].m_inputMap.at(InputEnum::Left);

		sf::Keyboard::Key rightKey =
			m_inputPtr->m_components[iIndex].m_inputMap.at(InputEnum::Right);

		sf::Keyboard::Key forwardKey =
			m_inputPtr->m_components[iIndex].m_inputMap.at(InputEnum::Up);

		if (InputManager::getInstance().getKeyDown(leftKey))
			return;
	}
}