#pragma once

#include "ECSView.hpp"
#include "System.hpp"

class PlayerInputSystem :
    public System
{
    PlayerInputSystem();
    void update(float deltaTime) override;
};

