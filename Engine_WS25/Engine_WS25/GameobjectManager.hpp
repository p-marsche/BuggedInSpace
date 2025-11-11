#pragma once

#include <SFML/Graphics.hpp>

#include <memory>
#include <string>
#include <unordered_map>

class GameObject;

class GameobjectManager
{
public:
	static GameobjectManager& getInstance();
    void init();
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void registerPlayer(std::string key, std::shared_ptr<GameObject> go);
    void activateProjectile(sf::Vector2f direction, int playerNumber);

private:
    std::unordered_map<std::string, std::shared_ptr<GameObject> > m_playerObjects;
    std::unordered_map<std::shared_ptr<GameObject>, bool> m_projectilePool;

    GameobjectManager() = default;
    ~GameobjectManager() = default;
    GameobjectManager(const GameobjectManager& rhv) = delete;
    GameobjectManager& operator =(GameobjectManager const&) = delete;
};
