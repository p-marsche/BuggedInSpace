#pragma once

#include "IComponent.h"
#include <SFML/Graphics.hpp>

class IRenderComponent :
    public IComponent
{
public:
    IRenderComponent(sf::Texture texture);
    virtual ~IRenderComponent() = default;
    void virtual Update(float deltaTime) override;
    void Draw(sf::RenderWindow& window);
    void SetSpritePosition(sf::Vector2f position);

private:
    sf::Sprite m_sprite;
};

