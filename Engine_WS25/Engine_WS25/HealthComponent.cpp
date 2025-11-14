#include "pch.h"

#include "HealthComponent.hpp"

HealthComponent::HealthComponent(int entityID, int maxHealth, float regenRate)
	: IComponent(entityID)
	, m_currentHealth(maxHealth)
	, m_maxHealth(maxHealth)
	, m_regenRate(regenRate)
	, m_regenAccumulator(0.f)
{ }
