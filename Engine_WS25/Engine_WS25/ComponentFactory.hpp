#pragma once

#include "InputComponent.hpp"
#include "RenderComponent.hpp"

#include "pch.h"

class ComponentFactory
{
public:
	static ComponentFactory& getInstance();
    std::shared_ptr<RenderComponent> createRenderComponent(sf::Texture& texture);
    std::shared_ptr<InputComponent> createInputComponent(int playerNumber);

private:
    ComponentFactory() = default;
    ~ComponentFactory() = default;
    ComponentFactory(const ComponentFactory&) = delete;
    ComponentFactory& operator =(const ComponentFactory&) = delete;
};
