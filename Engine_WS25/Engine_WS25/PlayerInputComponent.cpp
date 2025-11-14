#include "pch.h"

#include "PlayerInputComponent.hpp"

PlayerInputComponent::PlayerInputComponent(int entityID, std::unordered_map<sf::Keyboard::Key, InputEnum> inputMap)
	: IComponent(entityID)
	, m_inputMap(inputMap)
{ }