#pragma once

#include "IComponent.h"
#include <SFML/Graphics.hpp>

class RenderComponent :
    public IComponent
{
public:
    RenderComponent(sf::Texture& texture);
    virtual ~RenderComponent() = default;
    void virtual Update(float deltaTime) override;
    void Draw(sf::RenderWindow& window);
    void SetSpritePosition(sf::Vector2f position);

private:
    sf::Sprite m_sprite;
};

