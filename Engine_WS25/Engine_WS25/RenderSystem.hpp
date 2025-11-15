#pragma once

#include "SFML/Graphics.hpp"

#include "ECSView.hpp"
#include "System.hpp"
#include "RenderComponent.hpp"
#include "TransformComponent.hpp"

class RenderSystem :
    public System
{
public:
    RenderSystem();
    void update(float deltaTime) override;
    void render(sf::RenderWindow& window);
    void sortView();

private:
    std::shared_ptr<ComponentBlock<RenderComponent>> m_renderPtr;
    std::shared_ptr<ComponentBlock<TransformComponent>> m_transformPtr;
};

