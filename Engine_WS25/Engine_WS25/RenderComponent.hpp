#pragma once

#include "IComponent.hpp"

class RenderComponent :
    public IComponent
{
public:
    RenderComponent(sf::Texture& texture);
    virtual ~RenderComponent() = default;
    sf::Sprite& getSprite() { return m_sprite; }
    void virtual update(float deltaTime) override;
    void draw(sf::RenderWindow& window);
    void setSpritePosition(sf::Vector2f position);

private:
    sf::Sprite m_sprite;
};
