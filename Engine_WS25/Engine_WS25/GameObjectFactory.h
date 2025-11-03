#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ComponentFactory.h"

class GameObjectFactory
{
public:
    static GameObjectFactory& GetInstance();
    std::unique_ptr<GameObject> CreatePlayer(int playerNumber);

private:
    GameObjectFactory() = default;
    ~GameObjectFactory() = default;
    GameObjectFactory(const GameObjectFactory& rhv) = delete;
    GameObjectFactory& operator=(GameObjectFactory const&) = delete;
};
