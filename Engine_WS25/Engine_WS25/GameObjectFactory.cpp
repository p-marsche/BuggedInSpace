#include "GameObjectFactory.h"
#include "ComponentTypeEnum.h"

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
	/*std::shared_ptr<RenderComponent> render = (playerNumber == 1) ?
		ComponentFactory::GetInstance().CreateRenderComponent(--insert player1 asset here--) :
		ComponentFactory::GetInstance().CreateRenderComponent(--insert player2 asset here--);
	player->AddComponent(ComponentType::Render, render);*/
	player->AddComponent(ComponentType::Input, ComponentFactory::GetInstance().CreateInputComponent(1));
	return player;
}
