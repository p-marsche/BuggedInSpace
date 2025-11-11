#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <unordered_map>

class GameObject;

class GameObjectManager
{
public:
	static GameObjectManager& getInstance();
    void init();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void registerPlayer(std::string key, std::shared_ptr<GameObject> go);
    void activateProjectile(int playerNumber);

private:
    std::unordered_map<std::string, std::shared_ptr<GameObject> > m_playerObjects;
    std::unordered_map<std::shared_ptr<GameObject>, bool> m_projectilePool;

    GameObjectManager() = default;
    ~GameObjectManager() = default;
    GameObjectManager(const GameObjectManager& rhv) = delete;
    GameObjectManager& operator =(GameObjectManager const&) = delete;
};
