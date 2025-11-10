#include "pch.h"

#include "AssetManager.hpp"
#include "ComponentTypeEnum.hpp"
#include "GameObjectFactory.hpp"

GameObjectFactory& GameObjectFactory::getInstance()
{
	static GameObjectFactory m_instance;
	return m_instance;
}

std::unique_ptr<GameObject> GameObjectFactory::createPlayer(int playerNumber)
{
	if ((playerNumber != 1) && (playerNumber != 2))
		//add exception here later?
		return nullptr;

	auto player = std::make_unique<GameObject>();
	std::string filename;
	std::string key;

	if (playerNumber == 1)
	{
		key = "Player1";
		filename = "Player_Ship1.png";
	}
	else
	{
		key = "Player2";
		filename = "Player_Ship2.png";
	}

	AssetManager::getInstance().loadTexture(key, filename);
	sf::Texture& player1Tex = AssetManager::getInstance().getTexture(key);
	std::shared_ptr<RenderComponent> render =
		ComponentFactory::getInstance().createRenderComponent(player1Tex);
	player->addComponent(ComponentType::Render, render);
	player->addComponent(ComponentType::Input, ComponentFactory::getInstance().createInputComponent(playerNumber));
	return player;
}
