#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "ComponentFactory.hpp"

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
