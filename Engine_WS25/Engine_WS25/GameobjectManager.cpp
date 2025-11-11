#include "pch.h"

#include "AssetManager.hpp"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"
#include "GameObjectManager.hpp"

GameObjectManager& GameObjectManager::getInstance()
{
	static GameObjectManager m_instance;
	return m_instance;
}

void GameObjectManager::init()
{
	int i = 0;
	do {
		m_projectilePool.emplace(GameObjectFactory::getInstance().createProjectile(sf::Vector2f(0.f, 0.f)), false);
		i++;
	} while (i < 20);
}

void GameObjectManager::update(float deltaTime)
{
	for (auto& [go, flag] : m_projectilePool)
	{
		if (flag)
		{
			go->update(deltaTime);
		}
	}
	return;
}

void GameObjectManager::draw(sf::RenderWindow& window)
{
	sf::Vector2f topLeft = window.getView().getCenter() - (window.getView().getSize() / 2.f);
	sf::Vector2f bottomRight = window.getView().getCenter() + (window.getView().getSize() / 2.f);

	for (auto& [key, go] : m_playerObjects)
		go->draw(window);

	for (auto& [go, flag] : m_projectilePool)
	{
		if (flag)
		{
			go->draw(window);
			if (go->getObjectPosition().x > bottomRight.x + 100.f)
				flag = false;
		}
	}

}

void GameObjectManager::activateProjectile(int playerNumber)
{
	if (playerNumber != 1 && playerNumber != 2)
		return;

	std::string key = "Player" + std::to_string(playerNumber);
	std::string projectileKey = "Projectile" + std::to_string(playerNumber);
	for (auto& [go, flag] : m_projectilePool)
	{
		if (!flag)
		{
			flag = true;
			go->SetMoveDirection(sf::Vector2f(1.f, 0.f));
			sf::Vector2f currPos = go->getObjectPosition();
			sf::Vector2f playerPos = m_playerObjects[key]->getObjectPosition();
			float offset =
				m_playerObjects[key]->getSprite()->getGlobalBounds().width / 2.f + go->getSprite()->getGlobalBounds().width;
			go->moveObject(playerPos - currPos + sf::Vector2f(offset, 0.f));
			sf::Texture& projectileTex = AssetManager::getInstance().getTexture(projectileKey);
			go->getSprite()->setTexture(projectileTex);
			return;
		}
	}
			
}

void GameObjectManager::registerPlayer(std::string key, std::shared_ptr<GameObject> go)
{
	m_playerObjects.try_emplace(key, go);
}
