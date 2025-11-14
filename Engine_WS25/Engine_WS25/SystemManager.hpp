#pragma once

#include <memory>

#include "SystemType.hpp"
#include ""

class System;

namespace sf
{
    class RenderWindow;
}

class SystemManager
{
public:
	static SystemManager& getInstance();
    void init();

    void update(float deltaTime);
    void render(sf::RenderWindow& window);

private:
    SystemManager() = default;
    ~SystemManager() = default;
    SystemManager(const SystemManager& rhv) = delete;
    SystemManager& operator =(SystemManager const&) = delete;

    std::unordered_map<SystemType, std::shared_ptr<System>> m_systems;
};

