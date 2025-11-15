#pragma once

#include <memory>

#include "Entity.hpp"
#include "ComponentBlock.hpp"
#include "InputEnum.hpp"

struct ECSView;

class Registry
{
public:
	static Registry& getInstance();
    void init(int reserveCount);
    void update();

    int addEntity();
    void removeEntity(int entityID);

    void createHealthComponent(int entityID, int maxHealth, float regenRate);
    void createPhysicsComponent(int entityID, float maxVel, float acellRate, 
        float radiusFactor, float turnRate);
    void createPlayerInputComponent(int entityID, 
        std::unordered_map<InputEnum, sf::Keyboard::Key> inputMap);
    void createRenderComponent(int entityID, sf::Texture& texture, bool visible, 
        int zIndex, sf::Vector2f scale);
    void createStatusComponent(int entityID, bool destructible);
    void createTransformComponent(int entityID, sf::Vector2f position, sf::Vector2f scale, 
        sf::Vector2f forward);
    void removeComponent(int entityID, ComponentType type);

    std::shared_ptr<ECSView> getView(const std::vector<ComponentType> comps);
    std::unordered_map<ComponentType, std::shared_ptr<IComponentBlock>> m_componentBlocks;
    std::unordered_map<ComponentType, bool> m_blockIsDirty;

private:
    Registry() = default;
    ~Registry() = default;
    Registry(const Registry&) = delete;
    Registry& operator =(const Registry&) = delete;

    ComponentType getShortest(const std::vector<ComponentType> types);
    std::unordered_map<int, std::shared_ptr<Entity>> m_entityMap;
};
