#pragma once

#include "IComponent.hpp"
#include <memory>

class Texture;
class Sprite;

struct RenderComponent :
    public IComponent
{
public:
    RenderComponent(int entityID, sf::Texture& texture, bool visible,
        int zIndex, sf::Vector2f scale);
    virtual ~RenderComponent() = default;

    virtual ComponentType GetType() override { return m_type; }

    static constexpr ComponentType m_type = ComponentType::Render;

    sf::Sprite m_sprite;
    bool m_isVisible;
    int m_zIndex;
};
