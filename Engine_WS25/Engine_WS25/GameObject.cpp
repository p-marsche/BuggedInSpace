#include "GameObject.h"

GameObject::GameObject()
{
	m_nextID = 0;
	m_ID = m_nextID;
	m_nextID++;
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
	// need RenderComponent for useful implementation
}

void GameObject::AddComponent(std::string compType, IComponent* comp)
{
	if (m_components.find(compType) != m_components.end())
		return;

	m_components.insert({ compType, std::make_unique<IComponent>(comp) });
}

void GameObject::RemoveComponent(std::string compType)
{
	if (m_components.find(compType) == m_components.end())
		return;

	m_components.erase(compType);
}