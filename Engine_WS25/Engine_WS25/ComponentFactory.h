#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "RenderComponent.h"
#include "InputComponent.h"

class ComponentFactory
{
public:
	static ComponentFactory& GetInstance();
    std::shared_ptr<RenderComponent> CreateRenderComponent(sf::Texture& texture);
    std::shared_ptr<InputComponent> CreateInputComponent(int playerNumber);

private:
    ComponentFactory() = default;
    ~ComponentFactory() = default;
    ComponentFactory(const ComponentFactory& rhv) = delete;
    ComponentFactory& operator=(ComponentFactory const&) = delete;
};

