#pragma once

#include "ECSView.hpp"
#include "System.hpp"
#include "HealthComponent.hpp"
#include "StatusComponent.hpp"
#include "TransformComponent.hpp"

class HealthSystem :
    public System
{
public:
    HealthSystem();
    void update(float deltaTime) override;

    std::shared_ptr<ComponentBlock<HealthComponent>> m_healthPtr;
    std::shared_ptr<ComponentBlock<StatusComponent>> m_statusPtr;
    std::shared_ptr<ComponentBlock<TransformComponent>> m_transformPtr;
};

