#pragma once

#include "ComponentBlock.hpp"
#include "ECSView.hpp"
#include "PhysicsComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "System.hpp"
#include "TransformComponent.hpp"

class PlayerInputSystem :
    public System
{
public:
    PlayerInputSystem();
    void update(float deltaTime) override;

private:
    std::shared_ptr<ComponentBlock<PhysicsComponent>> m_physicsPtr;
    std::shared_ptr<ComponentBlock<PlayerInputComponent>> m_inputPtr;
    std::shared_ptr<ComponentBlock<TransformComponent>> m_transformPtr;
};

