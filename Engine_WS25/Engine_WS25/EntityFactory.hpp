#pragma once

#include "Registry.hpp"

#include <string>

class EntityFactory
{
public:
    static EntityFactory& getInstance();
    void init();
    int createPlayer(sf::Vector2f position, sf::Vector2f scale, sf::Vector2f forward, 
            std::string textureKey, float hitboxScale, float turnRate);
    int createBackground(sf::Vector2f scale, std::string textureKey);

private:
    EntityFactory() = default;
    ~EntityFactory() = default;
    EntityFactory(const EntityFactory&) = delete;
    EntityFactory& operator =(EntityFactory const&) = delete;
};
