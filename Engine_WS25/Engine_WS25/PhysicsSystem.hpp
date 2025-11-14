#pragma once

#include "ECSView.hpp"
#include "System.hpp"

class PhysicsSystem :
    public System
{
public:
    PhysicsSystem();
    void update(float deltaTime) override;
};

