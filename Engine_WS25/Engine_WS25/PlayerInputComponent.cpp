#include "pch.h"

#include "PlayerInputComponent.hpp"

PlayerInputComponent::PlayerInputComponent(int entityID,
	std::unordered_map<InputEnum, sf::Keyboard::Key> inputMap)
	: IComponent(entityID)
{ 
	for (auto& [key, val] : inputMap)
		m_inputMap.emplace(key, val);
}