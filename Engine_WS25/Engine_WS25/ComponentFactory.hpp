#pragma once

#include "AiInputComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "RenderComponent.hpp"

class ComponentFactory
{
public:
	static ComponentFactory& getInstance();
    std::shared_ptr<RenderComponent> createRenderComponent(sf::Texture& texture);
    std::shared_ptr<PlayerInputComponent> createPlayerInputComponent(int playerNumber);
    std::shared_ptr<AiInputComponent> createAiInputComponent();

private:
    ComponentFactory() = default;
    ~ComponentFactory() = default;
    ComponentFactory(const ComponentFactory&) = delete;
    ComponentFactory& operator =(const ComponentFactory&) = delete;
};
