#pragma once

#include "IComponent.hpp"

#include "SFML/Graphics.hpp"

struct PhysicsComponent :
    public IComponent
{
public:
    PhysicsComponent(int entityID, float maxVel, float acellRate, float radius);

    sf::Vector2f m_velocity;
    sf::Vector2f m_acceleration;
    float m_maxVelocity;
    float m_accelerationRate;
    float m_colliderRadius;
    // float m_turnRate;
    // float m_bounciness;
};

