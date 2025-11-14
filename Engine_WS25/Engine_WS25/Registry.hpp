#pragma once

#include <memory>

#include "Entity.hpp"
#include "ComponentBlock.hpp"
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
    void init(int reserveCount);

    int addEntity();
    void removeEntity(int entityID);
    void createHealthComponent(int entityID, int maxHealth, float regenRate);
    void createPhysicsComponent(int entityID, float maxVel, float acellRate, float radiusFactor);
    void createPlayerInputComponent(int entityID, std::unordered_map<sf::Keyboard::Key, InputEnum> inputMap);
    void createRenderComponent(int entityID, sf::Texture& texture, bool visible);
    void createStatusComponent(int entityID, bool destructible);
    void createTransformComponent(int entityID, sf::Vector2f position, sf::Vector2f scale, sf::Vector2f forward);
    void removeComponent(int entityID, ComponentType type);

private:
    Registry() = default;
    ~Registry() = default;
    Registry(const Registry&) = delete;
    Registry& operator =(const Registry&) = delete;

    std::unordered_map<ComponentType, std::shared_ptr<IComponentBlock>> m_componentBlocks;
    std::unordered_map<ComponentType, bool> m_blockIsDirty;
    std::unordered_map<int, std::shared_ptr<Entity>> m_entityMap;
};
