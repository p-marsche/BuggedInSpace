#pragma once

#include "IComponent.hpp"

struct HealthComponent :
    public IComponent
{
public:
    HealthComponent(int entityID, int maxHealth, float regenRate);

    int m_currentHealth;
    int m_maxHealth;
    float m_regenRate;
    float m_regenAccumulator;
};

