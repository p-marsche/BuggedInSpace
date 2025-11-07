#include "GameObjectFactory.h"
#include "ComponentTypeEnum.h"
#include <iostream>
#include <filesystem>

GameObjectFactory& GameObjectFactory::GetInstance()
{
	static GameObjectFactory m_instance;
	return m_instance;
}

std::unique_ptr<GameObject> GameObjectFactory::CreatePlayer(int playerNumber)
{
	if (playerNumber != 1 && playerNumber != 2)
		return nullptr;

	auto player = std::make_unique<GameObject>();
	std::string filename = "Player1_Ship.png";
	std::unique_ptr<sf::Texture> player1Tex = std::make_unique<sf::Texture>();
	player1Tex->loadFromFile("../Engine_WS25/Assets/Textures/" + filename);

	/*std::shared_ptr<RenderComponent> render = (playerNumber == 1) ?
		ComponentFactory::GetInstance().CreateRenderComponent(--insert player1 asset here--) :
		ComponentFactory::GetInstance().CreateRenderComponent(--insert player2 asset here--);*/
	std::shared_ptr<RenderComponent> render =
		ComponentFactory::GetInstance().CreateRenderComponent(*player1Tex);
	player->AddComponent(ComponentType::Render, render);
	player->AddComponent(ComponentType::Input, ComponentFactory::GetInstance().CreateInputComponent(1));
	return player;
}
