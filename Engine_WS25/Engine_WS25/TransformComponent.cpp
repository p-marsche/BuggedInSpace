#include "pch.h"

#include "TransformComponent.hpp"

TransformComponent::TransformComponent(int entityID, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f forward)
	: IComponent(entityID)
	, m_position(position)
	, m_scale(scale)
	, m_forward(forward)
{ }