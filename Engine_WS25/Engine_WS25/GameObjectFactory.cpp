#include "GameObjectFactory.h"

GameObjectFactory& GameObjectFactory::GetInstance()
{
	static GameObjectFactory m_instance;
	return m_instance;
}

std::unique_ptr<GameObject> GameObjectFactory::CreatePlayer(int playerNumber)
{
	auto player = std::make_unique<GameObject>();
	//player->AddComponent("Render", ComponentFactory::GetInstance().CreateRenderComponent(--insert asset here--);
	player->AddComponent("Input", ComponentFactory::GetInstance().CreateInputComponent(1));
	return player;
}
