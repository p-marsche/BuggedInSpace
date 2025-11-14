#include "pch.h"

#include "ComponentType.hpp"
#include "Registry.hpp"
#include "PlayerInputSystem.hpp"

PlayerInputSystem::PlayerInputSystem()
{
	m_requiredComponents.push_back(ComponentType::Physics);
	m_requiredComponents.push_back(ComponentType::PlayerInput);
	m_requiredComponents.push_back(ComponentType::Transform);
	m_view = Registry::getInstance().getView(m_requiredComponents);
}

void PlayerInputSystem::update(float dT)
{

}