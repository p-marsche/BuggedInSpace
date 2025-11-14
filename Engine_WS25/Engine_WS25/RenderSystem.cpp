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
}

void RenderSystem::update(float dT)
{

}
