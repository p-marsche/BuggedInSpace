#include "pch.h"

#include "AssetManager.hpp"
#include "EntityFactory.hpp"
#include "Entity.hpp"

int EntityFactory::createPlayer(sf::Vector2f position, sf::Vector2f scale, sf::Vector2f forward, 
		std::string textureKey, float hitboxScale, float turnRate)
{
	int entityID = Registry::getInstance().addEntity();
	sf::Texture& texture = AssetManager::getInstance().getTexture(textureKey);
	Registry::getInstance().createHealthComponent(entityID, 100, 10);
	Registry::getInstance().createRenderComponent(entityID, texture, true);
	Registry::getInstance().createPhysicsComponent(entityID, 30, 10, hitboxScale, turnRate);
	Registry::getInstance().createStatusComponent(entityID, false);
	Registry::getInstance().createTransformComponent(entityID, position, scale, forward);

	return entityID;
}

int EntityFactory::createBackground(sf::Vector2f scale, std::string textureKey)
{
	return 1;
}

int EntityFactory::createProjectile(sf::Vector2f moveDirection, std::string textureKey)
{
	return 1;
}
