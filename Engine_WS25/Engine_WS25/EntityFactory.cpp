#include "pch.h"

#include "AssetManager.hpp"
#include "EntityFactory.hpp"
#include "Entity.hpp"
#include "RenderComponent.hpp"

EntityFactory& EntityFactory::getInstance()
{
	static EntityFactory m_instance;
	return m_instance;
}

int EntityFactory::createPlayer(sf::Vector2f position, sf::Vector2f scale, 
	sf::Vector2f forward, std::string textureKey, float hitboxScale, float turnRate,
	std::unordered_map<InputEnum, sf::Keyboard::Key> inputMap)
{
	int entityID = Registry::getInstance().addEntity();
	sf::Texture& texture = AssetManager::getInstance().getTexture(textureKey);
	Registry::getInstance().createHealthComponent(entityID, 100, 10);
	Registry::getInstance().createRenderComponent(entityID, texture, true, 10, scale);

	std::shared_ptr<ComponentBlock<RenderComponent>> m_renderPtr =
		std::dynamic_pointer_cast<ComponentBlock<RenderComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Render));
	int compIndex = m_renderPtr->m_entityToIndex.at(entityID);
	auto hitbox = m_renderPtr->m_components[compIndex].m_sprite.getGlobalBounds();
	float colliderRadius = (hitbox.height > hitbox.width) ? hitbox.height : hitbox.width;
	colliderRadius *= hitboxScale*0.5f;

	Registry::getInstance().createPhysicsComponent(entityID, 30, 10, colliderRadius, turnRate);
	Registry::getInstance().createStatusComponent(entityID, false);
	Registry::getInstance().createTransformComponent(entityID, position, scale, forward);
	Registry::getInstance().createPlayerInputComponent(entityID, inputMap);

	return entityID;
}

int EntityFactory::createBackground(sf::Vector2f position, sf::Vector2f scale, 
	std::string textureKey)
{
	int entityID = Registry::getInstance().addEntity();
	sf::Texture& texture = AssetManager::getInstance().getTexture(textureKey);
	Registry::getInstance().createRenderComponent(entityID, texture, true, 0, scale);

	std::shared_ptr<ComponentBlock<RenderComponent>> m_renderPtr =
		std::dynamic_pointer_cast<ComponentBlock<RenderComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Render));
	int compIndex = m_renderPtr->m_entityToIndex.at(entityID);
	auto hitbox = m_renderPtr->m_components[compIndex].m_sprite.getGlobalBounds();

	Registry::getInstance().createTransformComponent(entityID, position, scale, 
		sf::Vector2f(0.f, 0.f));

	return entityID;
}

int EntityFactory::createFilledConsole(sf::Vector2f position, sf::Vector2f scale,
	sf::Vector2f forward, std::string textureKey)
{
	int entityID = Registry::getInstance().addEntity();
	sf::Texture& texture = AssetManager::getInstance().getTexture(textureKey);
	Registry::getInstance().createRenderComponent(entityID, texture, true, 5, scale);
	Registry::getInstance().createTransformComponent(entityID, position, scale, forward);
	return entityID;
}

int EntityFactory::createEmptyConsole(sf::Vector2f position, sf::Vector2f scale,
	sf::Vector2f forward, std::string textureKey, float hitboxScale)
{
	int entityID = Registry::getInstance().addEntity();
	sf::Texture& texture = AssetManager::getInstance().getTexture(textureKey);
	Registry::getInstance().createRenderComponent(entityID, texture, true, 7, scale);

	std::shared_ptr<ComponentBlock<RenderComponent>> m_renderPtr =
		std::dynamic_pointer_cast<ComponentBlock<RenderComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Render));
	int compIndex = m_renderPtr->m_entityToIndex.at(entityID);
	auto hitbox = m_renderPtr->m_components[compIndex].m_sprite.getGlobalBounds();
	float colliderRadius = (hitbox.height > hitbox.width) ? hitbox.height : hitbox.width;
	colliderRadius *= hitboxScale * 0.5f;

	Registry::getInstance().createPhysicsComponent(entityID, 0, 0, colliderRadius, 0);
	Registry::getInstance().createStatusComponent(entityID, false);
	Registry::getInstance().createTransformComponent(entityID, position, scale, forward);

	return entityID;
}

int EntityFactory::createString(sf::Vector2f position, sf::Vector2f scale,
	sf::Vector2f forward, std::string textureKey, float hitboxScale)
{
	int entityID = Registry::getInstance().addEntity();
	sf::Texture& texture = AssetManager::getInstance().getTexture(textureKey);
	Registry::getInstance().createHealthComponent(entityID, 100, 10);
	Registry::getInstance().createRenderComponent(entityID, texture, true, 8, scale);

	std::shared_ptr<ComponentBlock<RenderComponent>> m_renderPtr =
		std::dynamic_pointer_cast<ComponentBlock<RenderComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Render));
	int compIndex = m_renderPtr->m_entityToIndex.at(entityID);
	auto hitbox = m_renderPtr->m_components[compIndex].m_sprite.getGlobalBounds();
	float colliderRadius = (hitbox.height > hitbox.width) ? hitbox.height : hitbox.width;
	colliderRadius *= hitboxScale * 0.5f;

	Registry::getInstance().createPhysicsComponent(entityID, 0, 0, colliderRadius, 0);
	Registry::getInstance().createStatusComponent(entityID, false);
	Registry::getInstance().createTransformComponent(entityID, position, scale, forward);

	return entityID;
}