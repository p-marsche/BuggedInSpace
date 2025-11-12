#include "pch.h"

#include "ComponentFactory.hpp"

ComponentFactory& ComponentFactory::getInstance()
{
	static ComponentFactory m_instance;
	return m_instance;
}

std::shared_ptr<RenderComponent> ComponentFactory::createRenderComponent(sf::Texture& texture)
{
	return std::make_shared<RenderComponent>(texture);
}

std::shared_ptr<PlayerInputComponent> ComponentFactory::createPlayerInputComponent(int playerNumber)
{
	return std::make_shared<PlayerInputComponent>(playerNumber);
}

std::shared_ptr<AiInputComponent> ComponentFactory::createAiInputComponent(sf::Vector2f direction)
{
	auto comp = std::make_shared<AiInputComponent>();
	comp->SetMoveDirection(direction);
	return comp;
}