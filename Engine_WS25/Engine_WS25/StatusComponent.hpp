#pragma once

#include "IComponent.hpp"

struct StatusComponent :
    public IComponent
{
public:
    StatusComponent(int entityID, bool destructible, std::string tag);

    virtual ComponentType GetType() override { return m_type; }

    static constexpr ComponentType m_type = ComponentType::Status;

    bool m_isDestructible;
    bool m_collided;
    std::string m_tag;
};
