#pragma once

#include "IComponent.h"
#include <SFML/Graphics.hpp>

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

