#include "ComponentFactory.h"

ComponentFactory& ComponentFactory::GetInstance()
{
	static ComponentFactory m_instance;
	return m_instance;
}

std::unique_ptr<RenderComponent> ComponentFactory::CreateRenderComponent(sf::Texture& texture)
{
	return std::make_unique<RenderComponent>(texture);
}

std::unique_ptr<InputComponent> ComponentFactory::CreateInputComponent(int playerNumber)
{
	return std::make_unique<InputComponent>(playerNumber);
}