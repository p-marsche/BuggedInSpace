#include "pch.h"

#include "StatusComponent.hpp"

StatusComponent::StatusComponent(int entityID, bool destructible)
	: IComponent(entityID)
	, m_isDestructible(destructible)
{ }
