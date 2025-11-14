#include "pch.h"

#include "Registry.hpp"

Registry& Registry::getInstance()
{
	static Registry m_instance;
	return m_instance;
}

void Registry::init(int reserveCount)
{
	m_componentBlocks.emplace(ComponentType::Health, std::make_shared<ComponentBlock<HealthComponent>>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Physics, std::make_shared<ComponentBlock<PhysicsComponent>>(reserveCount));
	m_componentBlocks.emplace(ComponentType::PlayerInput, std::make_shared<ComponentBlock<PlayerInputComponent>>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Render, std::make_shared<ComponentBlock<RenderComponent>>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Status, std::make_shared<ComponentBlock<StatusComponent>>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Transform, std::make_shared<ComponentBlock<TransformComponent>>(reserveCount));

	m_blockIsDirty.emplace(ComponentType::Health, false);
	m_blockIsDirty.emplace(ComponentType::Physics, false);
	m_blockIsDirty.emplace(ComponentType::PlayerInput, false);
	m_blockIsDirty.emplace(ComponentType::Render, false);
	m_blockIsDirty.emplace(ComponentType::Status, false);
	m_blockIsDirty.emplace(ComponentType::Transform, false);
}

int Registry::addEntity()
{
	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>();
	m_entityMap.insert({ newEntity->m_ID, newEntity });
	return newEntity->m_ID;
}

void Registry::createHealthComponent(int entityID, int maxHealth, float regenRate)
{
	std::shared_ptr block = 
		std::dynamic_pointer_cast<ComponentBlock<HealthComponent>>(m_componentBlocks.at(ComponentType::Health));

	int newIndex = block->m_components.size();
	block->m_entities.push_back(entityID);
	block->m_entityToIndex.emplace(entityID, newIndex);
	block->m_components.emplace_back(entityID, maxHealth, regenRate);
}

void Registry::createPhysicsComponent(int entityID, float maxVel, float acellRate, float radiusFactor)
{
	std::shared_ptr block = 
		std::dynamic_pointer_cast<ComponentBlock<PhysicsComponent>>(m_componentBlocks.at(ComponentType::Physics));

	int newIndex = block->m_components.size();
	block->m_entities.push_back(entityID);
	block->m_entityToIndex.emplace(entityID, newIndex);
	block->m_components.emplace_back(entityID, maxVel, acellRate, radiusFactor);
}

void Registry::createPlayerInputComponent(int entityID, 
	std::unordered_map<sf::Keyboard::Key, InputEnum> inputMap)
{
	std::shared_ptr block = 
		std::dynamic_pointer_cast<ComponentBlock<PlayerInputComponent>>(m_componentBlocks.at(ComponentType::PlayerInput));

	int newIndex = block->m_components.size();
	block->m_entities.push_back(entityID);
	block->m_entityToIndex.emplace(entityID, newIndex);
	block->m_components.emplace_back(entityID, inputMap);
}

void Registry::createRenderComponent(int entityID, sf::Texture& texture, bool visible)
{
	std::shared_ptr block = 
		std::dynamic_pointer_cast<ComponentBlock<RenderComponent>>(m_componentBlocks.at(ComponentType::Render));

	int newIndex = block->m_components.size();
	block->m_entities.push_back(entityID);
	block->m_entityToIndex.emplace(entityID, newIndex);
	block->m_components.emplace_back(entityID, texture, visible);
}

void Registry::createStatusComponent(int entityID, bool destructible)
{
	std::shared_ptr block = 
		std::dynamic_pointer_cast<ComponentBlock<StatusComponent>>(m_componentBlocks.at(ComponentType::Status));

	int newIndex = block->m_components.size();
	block->m_entities.push_back(entityID);
	block->m_entityToIndex.emplace(entityID, newIndex);
	block->m_components.emplace_back(entityID, destructible);
}

void Registry::createTransformComponent(int entityID, sf::Vector2f position, 
	sf::Vector2f scale, sf::Vector2f forward)
{
	std::shared_ptr block = 
		std::dynamic_pointer_cast<ComponentBlock<TransformComponent>>(m_componentBlocks.at(ComponentType::Transform));

	int newIndex = block->m_components.size();
	block->m_entities.push_back(entityID);
	block->m_entityToIndex.emplace(entityID, newIndex);
	block->m_components.emplace_back(entityID, position, scale, forward);
}