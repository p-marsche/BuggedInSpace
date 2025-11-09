#include "ComponentFactory.hpp"

ComponentFactory& ComponentFactory::getInstance()
{
	static ComponentFactory m_instance;
	return m_instance;
}

std::shared_ptr<RenderComponent> ComponentFactory::createRenderComponent(sf::Texture& texture)
{
	return std::make_unique<RenderComponent>(texture);
}

std::shared_ptr<InputComponent> ComponentFactory::createInputComponent(int playerNumber)
{
	return std::make_unique<InputComponent>(playerNumber);
}
