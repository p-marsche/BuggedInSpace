#include "pch.h"

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
		processAcelleration(i, dT);

	for (unsigned int i = 0; i < m_view->m_entities.size(); i++)
		processColissions(i, dT);
}

void PhysicsSystem::processAcelleration(unsigned int index, float dT)
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
}

void PhysicsSystem::processColissions(unsigned int index, float dT)
{

}