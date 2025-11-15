#include "pch.h"

#include "ComponentType.hpp"
#include "Registry.hpp"
#include "RenderSystem.hpp"

RenderSystem::RenderSystem()
{
	m_requiredComponents.push_back(ComponentType::Render);
	m_requiredComponents.push_back(ComponentType::Transform);

	m_renderPtr =
		std::dynamic_pointer_cast<ComponentBlock<RenderComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Render));
	m_transformPtr =
		std::dynamic_pointer_cast<ComponentBlock<TransformComponent>>
		(Registry::getInstance().m_componentBlocks.at(ComponentType::Transform));

	m_view = Registry::getInstance().getView(m_requiredComponents);
	sortView();
}

void RenderSystem::update(float dT)
{
	if (checkView())
		sortView();

	for (unsigned int i = 0; i < m_view->m_entities.size(); i++)
	{
		int tIndex = m_view->m_componentVecs.at(ComponentType::Transform)[i];
		int rIndex = m_view->m_componentVecs.at(ComponentType::Render)[i];

		m_renderPtr->m_components[rIndex].m_sprite.setPosition
		(m_transformPtr->m_components[tIndex].m_position);

		m_renderPtr->m_components[rIndex].m_sprite.rotate
		(m_transformPtr->m_components[tIndex].m_newRotation);
	}
}

void RenderSystem::render(sf::RenderWindow& window)
{

	for (unsigned int i = 0; i < m_view->m_entities.size(); i++)
	{
		int rIndex = m_view->m_componentVecs.at(ComponentType::Render)[i];
		window.draw(m_renderPtr->m_components[rIndex].m_sprite);
	}
}

void RenderSystem::sortView()
{
	auto sortZIndex = [](const RenderComponent& a, const RenderComponent& b)
		{
			return a.m_zIndex < b.m_zIndex;
		};

	std::sort(m_renderPtr->m_components.begin(), m_renderPtr->m_components.end(), sortZIndex);

	m_renderPtr->m_entities.clear();
	for (auto& rend : m_renderPtr->m_components)
	{
		m_renderPtr->m_entityToIndex.at(rend.m_entityID) = m_renderPtr->m_entities.size();
		m_renderPtr->m_entities.push_back(rend.m_entityID);
	}

	m_view = Registry::getInstance().getView(m_requiredComponents);
}
