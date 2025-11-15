#pragma once

#include "ECSView.hpp"
#include "System.hpp"
#include "RenderComponent.hpp"
#include "TransformComponent.hpp"

class RenderSystem :
    public System
{
    RenderSystem();
    void update(float deltaTime) override;

private:
    std::shared_ptr<ComponentBlock<RenderComponent>> m_renderPtr;
    std::shared_ptr<ComponentBlock<TransformComponent>> m_transformPtr;


};

