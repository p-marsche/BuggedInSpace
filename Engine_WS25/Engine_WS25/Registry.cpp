#include "pch.h"

#include "Registry.hpp"

Registry& Registry::getInstance()
{
	static Registry m_instance;
	return m_instance;
}

void Registry::init(int reserveCount)
{
	m_componentBlocks.emplace(ComponentType::Health, std::make_shared<HealthComponent>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Physics, std::make_shared<PhysicsComponent>(reserveCount));
	m_componentBlocks.emplace(ComponentType::PlayerInput, std::make_shared<PlayerInputComponent>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Render, std::make_shared<RenderComponent>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Status, std::make_shared<StatusComponent>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Transform, std::make_shared<TransformComponent>(reserveCount));

	m_blockIsDirty.emplace(ComponentType::Health, false);
	m_blockIsDirty.emplace(ComponentType::Physics, false);
	m_blockIsDirty.emplace(ComponentType::PlayerInput, false);
	m_blockIsDirty.emplace(ComponentType::Render, false);
	m_blockIsDirty.emplace(ComponentType::Status, false);
	m_blockIsDirty.emplace(ComponentType::Transform, false);
}

void Registry::createHealthComponent(int entityID, int maxHealth, float regenRate)
{
	std::shared_ptr block = std::dynamic_pointer_cast<HealthComponent>(m_componentBlocks.at(ComponentType::Health));
}

void Registry::createPhysicsComponent(int entityID, float maxVel, float acellRate, float radius)
{
	std::shared_ptr block = std::dynamic_pointer_cast<PhysicsComponent>(m_componentBlocks.at(ComponentType::Physics));
}

void Registry::createPlayerInputComponent(int entityID, 
	std::unordered_map<sf::Keyboard::Key, InputEnum> inputMap)
{
	std::shared_ptr block = std::dynamic_pointer_cast<PlayerInputComponent>(m_componentBlocks.at(ComponentType::PlayerInput));
}

void Registry::createRenderComponent(int entityID, sf::Texture& texture, bool visible)
{
	std::shared_ptr block = std::dynamic_pointer_cast<RenderComponent>(m_componentBlocks.at(ComponentType::Render));
}

void Registry::createStatusComponent(int entityID, bool destructible)
{
	std::shared_ptr block = std::dynamic_pointer_cast<StatusComponent>(m_componentBlocks.at(ComponentType::Status));
}

void Registry::createTransformComponent(int entityID, sf::Vector2f position, 
	sf::Vector2f scale, sf::Vector2f forward)
{
	std::shared_ptr block = std::dynamic_pointer_cast<TransformComponent>(m_componentBlocks.at(ComponentType::Transform));
}