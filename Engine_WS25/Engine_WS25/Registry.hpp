#pragma once

#include "HealthComponent.hpp"
#include "PhysicsComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "RenderComponent.hpp"
#include "StatusComponent.hpp"
#include "TransformComponent.hpp"

class Registry
{
public:
	static Registry& getInstance();
    void Init(int reserveCount);

    int addEntity();
    void createHealthComponent(int entityID, int maxHealth, float regenRate);
    void createPhysicsComponent(int entityID, float maxVel, float acellRate, float radiusFactor);
    void createPlayerInputComponent(int entityID, std::unordered_map<sf::Keyboard::Key, InputEnum> inputMap);
    void createRenderComponent(int entityID, sf::Texture& texture, bool visible);
    void createStatusComponent(int entityID, bool destructible);
    void createTransformComponent(int entityID, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f forward);

private:
    Registry() = default;
    ~Registry() = default;
    Registry(const Registry&) = delete;
    Registry& operator =(const Registry&) = delete;
};
