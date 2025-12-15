#include "pch.h"

#include "Manifold.hpp"
#include "MissionManager.hpp"
#include "Registry.hpp"
#include "PhysicsSystem.hpp"
#include "VectorUtils.hpp"

PhysicsSystem::PhysicsSystem()
{
	m_requiredComponents.push_back(ComponentType::Physics);
	m_requiredComponents.push_back(ComponentType::Status);
	m_requiredComponents.push_back(ComponentType::Transform);

	m_physicsPtr =
		std::dynamic_pointer_cast<ComponentBlock<PhysicsComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Physics));
	m_statusPtr =
		std::dynamic_pointer_cast<ComponentBlock<StatusComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Status));
	m_transformPtr =
		std::dynamic_pointer_cast<ComponentBlock<TransformComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Transform));

	m_view = Registry::getInstance().getView(m_requiredComponents);
}

void PhysicsSystem::update(float dT)
{
	checkView();

	for (unsigned int i = 0; i < m_view->m_entities.size(); i++)
		processMovement(i, dT);

	for (unsigned int i = 0; i < m_view->m_entities.size()-1; i++)
		processColissions(i, dT);
}

void PhysicsSystem::processMovement(unsigned int index, float dT)
{
	int pIndex = m_view->m_componentVecs.at(ComponentType::Physics)[index];
	int sIndex = m_view->m_componentVecs.at(ComponentType::Status)[index];
	int tIndex = m_view->m_componentVecs.at(ComponentType::Transform)[index];

	sf::Vector2f newVel = m_physicsPtr->m_components[pIndex].m_velocity;
	sf::Vector2f currAcell = m_physicsPtr->m_components[pIndex].m_acceleration;
	float acellRate = m_physicsPtr->m_components[pIndex].m_accelerationRate;
	float maxVel = m_physicsPtr->m_components[pIndex].m_maxVelocity;
	newVel = newVel + (currAcell * acellRate * dT);
	newVel = VecUtils::clamp(newVel, maxVel);
	m_physicsPtr->m_components[pIndex].m_velocity = newVel;

	m_transformPtr->m_components[tIndex].m_position +=
		m_physicsPtr->m_components[pIndex].m_velocity;

	m_statusPtr->m_components[sIndex].m_collided = false;
}

void PhysicsSystem::processColissions(unsigned int index, float dT)
{
	int pIndex1 = m_view->m_componentVecs.at(ComponentType::Physics)[index];
	int sIndex1 = m_view->m_componentVecs.at(ComponentType::Status)[index];
	int tIndex1 = m_view->m_componentVecs.at(ComponentType::Transform)[index];

	for (unsigned int j = index+1; j < m_view->m_entities.size(); j++)
	{
		int pIndex2 = m_view->m_componentVecs.at(ComponentType::Physics)[j];
		int sIndex2 = m_view->m_componentVecs.at(ComponentType::Status)[j];
		int tIndex2 = m_view->m_componentVecs.at(ComponentType::Transform)[j];

		sf::Vector2f dist =
			m_transformPtr->m_components[tIndex1].m_position -
			m_transformPtr->m_components[tIndex2].m_position;
		float combinedRadius =
			m_physicsPtr->m_components[pIndex1].m_colliderRadius +
			m_physicsPtr->m_components[pIndex2].m_colliderRadius;
		float combinedRadiusSquare = combinedRadius * combinedRadius;
		float sqDist = dist.x * dist.x + dist.y * dist.y;

		if (sqDist < combinedRadiusSquare)
		{
			m_statusPtr->m_components[sIndex1].m_collided = true;
			m_statusPtr->m_components[sIndex2].m_collided = true;
			notifyMissionManager(sIndex1, sIndex2);
		}
	}
}

void PhysicsSystem::notifyMissionManager(int sIndex1, int sIndex2)
{
	int id1 = m_statusPtr->m_components[sIndex1].m_entityID;
	int id2 = m_statusPtr->m_components[sIndex2].m_entityID;

	std::string tag1 = m_statusPtr->m_components[sIndex1].m_tag;
	std::string tag2 = m_statusPtr->m_components[sIndex2].m_tag;

	auto collManifold = Manifold(id1, id2, tag1, tag2);
	MissionManager::getInstance().processManifold(collManifold);
}