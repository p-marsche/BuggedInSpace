#include "pch.h"

#include "ComponentType.hpp"
#include "Registry.hpp"
#include "RenderSystem.hpp"

RenderSystem::RenderSystem()
{
	m_requiredComponents.push_back(ComponentType::Render);
	m_requiredComponents.push_back(ComponentType::Transform);
	m_view = Registry::getInstance().getView(m_requiredComponents);
}

void RenderSystem::update(float dT)
{

}
