#pragma once

#include "IComponent.hpp"
#include "SFML/Graphics.hpp"

struct TransformComponent
	: public IComponent
{
public:
	TransformComponent(int entityID, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f orientation);

	sf::Vector2f m_position;
	sf::Vector2f m_scale;
	sf::Vector2f m_forward;
	// alternative: float for orientation in degree?
};