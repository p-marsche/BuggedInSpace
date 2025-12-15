#include "pch.h"

#include "StatusComponent.hpp"

StatusComponent::StatusComponent(int entityID, bool destructible, std::string tag)
	: IComponent(entityID)
	, m_isDestructible(destructible)
	, m_collided(false)
	, m_tag(tag)
{ }
