#pragma once

#include "ComponentFactory.hpp"
#include "GameObject.hpp"

#include "pch.h"

class GameObjectFactory
{
public:
    static GameObjectFactory& getInstance();
    std::unique_ptr<GameObject> createPlayer(int playerNumber);

private:
    GameObjectFactory() = default;
    ~GameObjectFactory() = default;
    GameObjectFactory(const GameObjectFactory&) = delete;
    GameObjectFactory& operator =(GameObjectFactory const&) = delete;
};
