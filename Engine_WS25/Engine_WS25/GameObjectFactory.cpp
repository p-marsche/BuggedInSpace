#include "pch.h"

#include "AssetManager.hpp"
#include "ComponentTypeEnum.hpp"
#include "ComponentFactory.hpp"
#include "GameObject.hpp"
#include "GameObjectFactory.hpp"

GameObjectFactory& GameObjectFactory::getInstance()
{
	static GameObjectFactory m_instance;
	return m_instance;
}

std::shared_ptr<GameObject> GameObjectFactory::createPlayer(int playerNumber)
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

std::shared_ptr<GameObject> GameObjectFactory::createBackground(sf::Vector2f scale)
{
	auto background = std::make_unique<GameObject>();
	std::string filename = "Background.png";
	std::string key = "Background";

	AssetManager::getInstance().loadTexture(key, filename);
	sf::Texture& backgroundTex = AssetManager::getInstance().getTexture(key);
	std::shared_ptr<RenderComponent> render =
		ComponentFactory::getInstance().createRenderComponent(backgroundTex);
	render->getSprite().setScale(scale);
	sf::Vector2f newPos(render->getSprite().getGlobalBounds().width/2, render->getSprite().getGlobalBounds().height/2);
	background->addComponent(ComponentType::Render, render);
	background->moveObject(newPos);
	return background;
}