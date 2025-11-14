#pragma once

#include "IComponent.hpp"

struct HealthComponent :
    public IComponent
{
public:
    HealthComponent(int entityID, int maxHealth, float regenRate);

    virtual ComponentType GetType() override { return m_type; }

    static constexpr ComponentType m_type = ComponentType::Health;

    int m_currentHealth;
    int m_maxHealth;
    float m_regenRate;
    float m_regenAccumulator;
};

