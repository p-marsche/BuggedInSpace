#pragma once

#include "ComponentBlock.hpp"
#include "ECSView.hpp"
#include "System.hpp"
#include "PhysicsComponent.hpp"
#include "StatusComponent.hpp"
#include "TransformComponent.hpp"

class PhysicsSystem :
    public System
{
public:
    PhysicsSystem();
    void update(float deltaTime) override;

private:
    std::shared_ptr<ComponentBlock<PhysicsComponent>> m_physicsPtr;
    std::shared_ptr<ComponentBlock<StatusComponent>> m_statusPtr;
    std::shared_ptr<ComponentBlock<TransformComponent>> m_transformPtr;

    void processMovement(unsigned int index, float dT);
    void processColissions(unsigned int index, float dT);
};

