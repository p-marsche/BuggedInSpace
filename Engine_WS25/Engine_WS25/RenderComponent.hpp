#pragma once

#include "IComponent.hpp"

#include "pch.h"

class RenderComponent :
    public IComponent
{
public:
    RenderComponent(sf::Texture& texture);
    virtual ~RenderComponent() = default;
    void virtual update(float deltaTime) override;
    void draw(sf::RenderWindow& window);
    void setSpritePosition(sf::Vector2f position);

private:
    sf::Sprite m_sprite;
};
