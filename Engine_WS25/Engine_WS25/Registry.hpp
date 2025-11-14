#pragma once

#include <memory>

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

    std::unordered_map<ComponentType, std::shared_ptr<IComponentBlock>> m_componentBlocks;
    /*ComponentBlock<HealthComponent> m_healthBlock;
    ComponentBlock<PhysicsComponent> m_physicsBlock;
    ComponentBlock<PlayerInputComponent> m_playerInputBlock;
    ComponentBlock<RenderComponent> m_renderBlock;
    ComponentBlock<StatusComponent> m_statusBlock;
    ComponentBlock<TransformComponent> m_transformBlock;*/
    std::unordered_map<ComponentType, bool> m_blockIsDirty;
};
