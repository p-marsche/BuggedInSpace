#pragma once

#include "IComponent.hpp"
#include <memory>

class Texture;
class Sprite;

struct RenderComponent :
    public IComponent
{
public:
    RenderComponent(int entityID, sf::Texture& texture, bool visible);
    virtual ~RenderComponent() = default;

    sf::Texture& m_texture;
    sf::Sprite m_sprite;
    bool m_isVisible;
};
