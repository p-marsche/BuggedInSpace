
#include "pch.h"

#include "AssetManager.hpp"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include "GameobjectManager.hpp"

GameobjectManager& GameobjectManager::getInstance()
{
	static GameobjectManager m_instance;
	return m_instance;
}

void GameobjectManager::init()
{
	int i = 0;
	do {
		m_projectilePool.emplace(GameObjectFactory::getInstance().createProjectile(sf::Vector2f(0.f, 0.f)), false);
	} while (i < 20);
}

void GameobjectManager::update(float deltaTime)
{
	return;
}

void GameobjectManager::draw(sf::RenderWindow& window)
{
	for (auto& [key, go] : m_playerObjects)
		go->draw(window);

	for (auto& [go, flag] : m_projectilePool)
		if (flag)
			go->draw(window);
}

void GameobjectManager::activateProjectile(sf::Vector2f direction, int playerNumber)
{
	if (playerNumber != 1 && playerNumber != 2)
		return;

	for (auto& [go, flag] : m_projectilePool)
		if (!flag)
		{
			flag = true;
			go->SetMoveDirection(direction);
			std::string key = "Projectile" + std::to_string(playerNumber);
			sf::Texture& projectileTex =  AssetManager::getInstance().getTexture(key);
			go->getSprite()->setTexture(projectileTex);
			return;
		}
			
}

void GameobjectManager::registerPlayer(std::string key, std::shared_ptr<GameObject> go)
{
	m_playerObjects.try_emplace(key, go);
}
