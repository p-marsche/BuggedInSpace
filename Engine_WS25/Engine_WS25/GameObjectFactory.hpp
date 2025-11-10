#pragma once

class GameObject;

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
