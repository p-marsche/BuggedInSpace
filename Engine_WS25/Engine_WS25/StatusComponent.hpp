#pragma once

#include "IComponent.hpp"

struct StatusComponent :
    public IComponent
{
public:
    StatusComponent(int entityID, bool destructible);

    bool m_isDestructible;
};
