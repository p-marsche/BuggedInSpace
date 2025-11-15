#include "pch.h"

#include "ECSView.hpp"
#include "HealthComponent.hpp"
#include "PhysicsComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "Registry.hpp"
#include "RenderComponent.hpp"
#include "StatusComponent.hpp"
#include "TransformComponent.hpp"

Registry& Registry::getInstance()
{
	static Registry m_instance;
	return m_instance;
}

void Registry::init(int reserveCount)
{
	m_componentBlocks.emplace(ComponentType::Health, 
		std::make_shared<ComponentBlock<HealthComponent>>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Physics, 
		std::make_shared<ComponentBlock<PhysicsComponent>>(reserveCount));
	m_componentBlocks.emplace(ComponentType::PlayerInput, 
		std::make_shared<ComponentBlock<PlayerInputComponent>>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Render, 
		std::make_shared<ComponentBlock<RenderComponent>>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Status, 
		std::make_shared<ComponentBlock<StatusComponent>>(reserveCount));
	m_componentBlocks.emplace(ComponentType::Transform, 
		std::make_shared<ComponentBlock<TransformComponent>>(reserveCount));

	m_blockIsDirty.emplace(ComponentType::Health, true);
	m_blockIsDirty.emplace(ComponentType::Physics, true);
	m_blockIsDirty.emplace(ComponentType::PlayerInput, true);
	m_blockIsDirty.emplace(ComponentType::Render, true);
	m_blockIsDirty.emplace(ComponentType::Status, true);
	m_blockIsDirty.emplace(ComponentType::Transform, true);
}

void Registry::update()
{
	for (auto& [type, flag] : m_blockIsDirty)
		flag = false;
}

int Registry::addEntity()
{
	std::shared_ptr<Entity> newEntity = std::make_shared<Entity>();
	m_entityMap.insert({ newEntity->m_ID, newEntity });
	return newEntity->m_ID;
}

void Registry::removeEntity(int ID)
{
	for (auto& [type, block] : m_componentBlocks)
	{
		bool wasRemoved = block->remove(ID);
		if (wasRemoved)
			m_blockIsDirty.at(type) = true;
	}
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

void Registry::createPhysicsComponent(int entityID, float maxVel, float acellRate, 
		float radiusFactor, float turnRate)
{
	std::shared_ptr block = 
		std::dynamic_pointer_cast<ComponentBlock<PhysicsComponent>>(m_componentBlocks.at(ComponentType::Physics));

	int newIndex = block->m_components.size();
	block->m_entities.push_back(entityID);
	block->m_entityToIndex.emplace(entityID, newIndex);
	block->m_components.emplace_back(entityID, maxVel, acellRate, radiusFactor, turnRate);
}

void Registry::createPlayerInputComponent(int entityID, 
	std::unordered_map<InputEnum, sf::Keyboard::Key> inputMap)
{
	std::shared_ptr block = 
		std::dynamic_pointer_cast<ComponentBlock<PlayerInputComponent>>
		(m_componentBlocks.at(ComponentType::PlayerInput));

	int newIndex = block->m_components.size();
	block->m_entities.push_back(entityID);
	block->m_entityToIndex.emplace(entityID, newIndex);
	block->m_components.emplace_back(entityID, inputMap);
}

void Registry::createRenderComponent(int entityID, sf::Texture& texture, 
	bool visible, int zIndex, sf::Vector2f scale)
{
	std::shared_ptr block = 
		std::dynamic_pointer_cast<ComponentBlock<RenderComponent>>
		(m_componentBlocks.at(ComponentType::Render));

	int newIndex = block->m_components.size();
	block->m_entities.push_back(entityID);
	block->m_entityToIndex.emplace(entityID, newIndex);
	block->m_components.emplace_back(entityID, texture, visible, zIndex, scale);
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
		std::dynamic_pointer_cast<ComponentBlock<TransformComponent>>
		(m_componentBlocks.at(ComponentType::Transform));

	int newIndex = block->m_components.size();
	block->m_entities.push_back(entityID);
	block->m_entityToIndex.emplace(entityID, newIndex);
	block->m_components.emplace_back(entityID, position, scale, forward);
}

void Registry::removeComponent(int entityID, ComponentType type)
{
	m_componentBlocks.at(type)->remove(entityID);
}

sf::Vector2f Registry::getPlayerPosition(int entityID)
{
	auto block =
		std::dynamic_pointer_cast<ComponentBlock<TransformComponent>>
		(m_componentBlocks.at(ComponentType::Transform));

	int compIndex = block->m_entityToIndex.at(entityID);
	return block->m_components[compIndex].m_position;
}

ComponentType Registry::getShortest(std::vector<ComponentType> types)
{
	ComponentType shortest = types[0];
	unsigned int minLength = m_componentBlocks[types[0]]->m_entities.size();
	for (auto& t : types)
	{
		if (m_componentBlocks[t]->m_entities.size() < minLength)
		{
			shortest = t;
			minLength = m_componentBlocks[t]->m_entities.size();
		}
	}
	return shortest;
}

// create something akin to "Sparse set"
std::shared_ptr<ECSView> Registry::getView(const std::vector<ComponentType> types)
{
	auto result = std::make_shared<ECSView>();
	ComponentType shortest = getShortest(types);

	for (auto i : m_componentBlocks[shortest]->m_entities)
	{
		bool hasAll = true;
		for (auto t : types)
		{
			hasAll = (hasAll && m_componentBlocks[t]->hasID(i));
		}
		if (hasAll)
			result->m_entities.push_back(i);
	}

	//necessary to create empty vecs to push_back elements onto in next loop
	for (auto t : types)
		result->m_componentVecs[t];

	for (auto t : types)
	{
		for (int i : result->m_entities)
		{
			result->m_componentVecs[t].push_back(m_componentBlocks[t]->m_entityToIndex[i]);
		}
	}

	return result;
}