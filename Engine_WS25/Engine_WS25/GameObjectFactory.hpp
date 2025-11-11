#pragma once

class GameObject;

class GameObjectFactory
{
public:
    static GameObjectFactory& getInstance();
    std::shared_ptr<GameObject> createPlayer(int playerNumber);
    std::shared_ptr<GameObject> createBackground(sf::Vector2f scale);
    std::shared_ptr<GameObject> createProjectile();

private:
    GameObjectFactory() = default;
    ~GameObjectFactory() = default;
    GameObjectFactory(const GameObjectFactory&) = delete;
    GameObjectFactory& operator =(GameObjectFactory const&) = delete;
};
