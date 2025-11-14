#include "pch.h"

#include "Registry.hpp"

Registry& Registry::getInstance()
{
	static Registry m_instance;
	return m_instance;
}

void Registry::createHealthComponent(int entityID, int maxHealth, float regenRate)
{
	// HealthComponent(entityID, maxHealth, regenRate);
}

void Registry::createPhysicsComponent(int entityID, float maxVel, float acellRate, float radius)
{
	// PhysicsComponent(entityID, maxVel, acellRate, radius);
}

void Registry::createPlayerInputComponent(int entityID, 
	std::unordered_map<sf::Keyboard::Key, InputEnum> inputMap)
{
	// PlayerInputComponent(entityID, inputMap);
}

void Registry::createRenderComponent(int entityID, sf::Texture& texture, bool visible)
{
	// RenderComponent(entityID, texture, visible);
}

void Registry::createStatusComponent(int entityID, bool destructible)
{
	// StatusComponent(entityID, destructible);
}

void Registry::createTransformComponent(int entityID, sf::Vector2f position, 
	sf::Vector2f scale, sf::Vector2f forward)
{
	// TransformComponent(entityID, position, scale, forward);
}