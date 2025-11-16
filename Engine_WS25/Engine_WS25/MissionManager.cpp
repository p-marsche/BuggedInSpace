#include "pch.h"

#include "AssetManager.hpp"
#include "ComponentType.hpp"
#include "MissionManager.hpp"
#include "PhysicsComponent.hpp"
#include "StatusComponent.hpp"
#include "RenderComponent.hpp"

MissionManager& MissionManager::getInstance()
{
	static MissionManager m_instance;
	return m_instance;
}

void MissionManager::init(int threshold)
{
	m_inventoryCounter = 0;
	m_fillCounter = 0;
	m_missionThreshold = threshold;
	std::cout << m_missionThreshold << std::endl;
}

bool MissionManager::checkMission()
{
	return (m_fillCounter >= m_missionThreshold);
}

void MissionManager::processManifold(Manifold manifold)
{
	if (manifold.m_tag1 == "Player")
	{
		if (manifold.m_tag2 == "Empty")
			handleEmptyConsole(manifold.m_entityID2);

		else if (manifold.m_tag2 == "String")
			handleString(manifold.m_entityID2);
	}
	else if (manifold.m_tag2 == "Player")
	{
		if (manifold.m_tag1 == "Empty")
			handleEmptyConsole(manifold.m_entityID1);

		else if (manifold.m_tag1 == "String")
			handleString(manifold.m_entityID1);
	}
}

void MissionManager::handleEmptyConsole(int entityID)
{
	if (m_inventoryCounter == 0)
		return;

	std::shared_ptr<ComponentBlock<RenderComponent>> renderPtr =
		std::dynamic_pointer_cast<ComponentBlock<RenderComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Render));
	std::shared_ptr<ComponentBlock<StatusComponent>> statusPtr =
		std::dynamic_pointer_cast<ComponentBlock<StatusComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Status));

	int rIndex = renderPtr->m_entityToIndex.at(entityID);
	int sIndex = statusPtr->m_entityToIndex.at(entityID);

	statusPtr->m_components.at(sIndex).m_tag = "Other";
	sf::Texture& newTex = AssetManager::getInstance().getTexture("Filled");
	renderPtr->m_components.at(rIndex).m_sprite.setTexture(newTex);
	Registry::getInstance().
		removeComponent(entityID, ComponentType::Physics);

	m_inventoryCounter--;
	m_fillCounter++;
}

void MissionManager::handleString(int entityID)
{
	Registry::getInstance().removeEntity(entityID);
	m_inventoryCounter++;
}