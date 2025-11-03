#include "GameObject.h"

int GameObject::m_nextID = 0;

GameObject::GameObject()
	: m_ID(m_nextID++)
{
}

void GameObject::Update(float deltaTime)
{
	for (auto& [_, comp] : m_components)
	{
		comp->Update(deltaTime);
	}
}

void GameObject::Draw(sf::RenderWindow& window)
{
	if (m_renderComps.empty())
		return;

	for (auto& render : m_renderComps)
	{
		render.Draw(window);
	}
	// need RenderComponent for useful implementation
}

// add code to check for render-comp
void GameObject::AddComponent(std::string compType, std::unique_ptr<IComponent> comp)
{
	if (m_components.find(compType) != m_components.end())
		return;

	m_components.emplace(compType, std::move(comp));
}

// add code to check for render-comp
void GameObject::RemoveComponent(std::string compType)
{
	if (m_components.find(compType) == m_components.end())
		return;

	m_components.erase(compType);
}