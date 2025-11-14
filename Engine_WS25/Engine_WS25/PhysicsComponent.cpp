#include "pch.h"

#include "PhysicsComponent.hpp"

PhysicsComponent::PhysicsComponent(int entityID, float maxVel, 
	float acellRate, float radius, float turnRate)
	: IComponent(entityID)
	, m_maxVelocity(maxVel)
	, m_accelerationRate(acellRate)
	, m_colliderRadius(radius)
	, m_acceleration({ 0.f, 0.f })
	, m_velocity({ 0.f, 0.f })
	, m_turnRate(turnRate)
{ }
