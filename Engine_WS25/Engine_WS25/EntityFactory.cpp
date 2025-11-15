#include "pch.h"

#include "AssetManager.hpp"
#include "EntityFactory.hpp"
#include "Entity.hpp"
#include "RenderComponent.hpp"

int EntityFactory::createPlayer(sf::Vector2f position, sf::Vector2f scale, sf::Vector2f forward, 
		std::string textureKey, float hitboxScale, float turnRate)
{
	int entityID = Registry::getInstance().addEntity();
	sf::Texture& texture = AssetManager::getInstance().getTexture(textureKey);
	Registry::getInstance().createHealthComponent(entityID, 100, 10);
	Registry::getInstance().createRenderComponent(entityID, texture, true, 1);

	std::shared_ptr<ComponentBlock<RenderComponent>> m_renderPtr =
		std::dynamic_pointer_cast<ComponentBlock<RenderComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Render));
	int compIndex = m_renderPtr->m_entityToIndex.at(entityID);
	auto hitbox = m_renderPtr->m_components[compIndex].m_sprite.getGlobalBounds();
	float colliderRadius = (hitbox.height > hitbox.width) ? hitbox.height : hitbox.width;
	colliderRadius *= hitboxScale;

	Registry::getInstance().createPhysicsComponent(entityID, 30, 10, colliderRadius, turnRate);
	Registry::getInstance().createStatusComponent(entityID, false);
	Registry::getInstance().createTransformComponent(entityID, position, scale, forward);

	return entityID;
}

int EntityFactory::createBackground(sf::Vector2f scale, std::string textureKey)
{
	return 1;
}
