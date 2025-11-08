#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ComponentFactory.h"

class GameObjectFactory
{
public:
    static GameObjectFactory& getInstance();
    std::unique_ptr<GameObject> createPlayer(int playerNumber);

private:
    GameObjectFactory() = default;
    ~GameObjectFactory() = default;
    GameObjectFactory(const GameObjectFactory& rhv) = delete;
    GameObjectFactory& operator=(GameObjectFactory const&) = delete;
};
