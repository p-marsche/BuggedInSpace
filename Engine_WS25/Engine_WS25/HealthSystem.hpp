#pragma once

#include "ECSView.hpp"
#include "System.hpp"

class HealthSystem :
    public System
{
public:
    HealthSystem();
    void update(float deltaTime) override;

private:
    std::shared_ptr<ECSView> m_view;
};

