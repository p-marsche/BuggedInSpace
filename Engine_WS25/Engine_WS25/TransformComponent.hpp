#pragma once

#include "IComponent.hpp"
#include "SFML/Graphics.hpp"

struct TransformComponent
	: public IComponent
{
public:
	TransformComponent(int entityID, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f orientation);

	virtual ComponentType GetType() override { return m_type; }

	static constexpr ComponentType m_type = ComponentType::Transform;

	sf::Vector2f m_position;
	sf::Vector2f m_scale;
	sf::Vector2f m_forward;
	// alternative: float for orientation in degree?
};