#pragma once

#include "ECSView.hpp"
#include "System.hpp"

class RenderSystem :
    public System
{
    RenderSystem();
    void update(float deltaTime) override;
};

