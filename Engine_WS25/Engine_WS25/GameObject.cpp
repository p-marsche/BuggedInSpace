#include "GameObject.h"
#include <iostream>

int GameObject::m_nextID = 0;

GameObject::GameObject()
	: m_ID(m_nextID++)
{
}

void GameObject::Update(float deltaTime)
{
	for (auto& [ctype, comp] : m_components)
	{
		comp->Update(deltaTime);
		if (ctype == ComponentType::Input)
		{
			auto input = std::dynamic_pointer_cast<InputComponent>(comp);
			sf::Vector2f movement = input->GetMoveInput();
			movement = { movement.x * 1, movement.y * 1 };
			this->setPosition(this->getPosition() + movement);
		}
	}

}

void GameObject::Draw(sf::RenderWindow& window)
{
	auto rend = m_components.find(ComponentType::Render);
	if (rend == m_components.end())
		return;

	auto renderComp = std::dynamic_pointer_cast<RenderComponent>(rend->second);
	renderComp->SetSpritePosition(this->getPosition());
	renderComp->Draw(window);
}

void GameObject::AddComponent(ComponentType compType, std::shared_ptr<IComponent> comp)
{
	if (m_components.find(compType) != m_components.end())
		return;

	m_components.emplace(compType, std::move(comp));
}

void GameObject::RemoveComponent(ComponentType compType)
{
	if (m_components.find(compType) == m_components.end())
		return;

	m_components.erase(compType);
}