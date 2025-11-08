#include "GameObject.h"
#include <iostream>

int GameObject::m_nextID = 0;

GameObject::GameObject()
	: m_ID(m_nextID++)
{
}

void GameObject::update(float deltaTime)
{
	for (auto& [ctype, comp] : m_components)
	{
		comp->update(deltaTime);
		if (ctype == ComponentType::Input)
		{
			auto input = std::dynamic_pointer_cast<InputComponent>(comp);
			sf::Vector2f movement = input->getMoveInput();
			movement = { movement.x * 1, movement.y * 1 };
			this->setPosition(this->getPosition() + movement);
		}
	}

}

void GameObject::draw(sf::RenderWindow& window)
{
	auto rend = m_components.find(ComponentType::Render);
	if (rend == m_components.end())
		return;

	auto renderComp = std::dynamic_pointer_cast<RenderComponent>(rend->second);
	renderComp->setSpritePosition(this->getPosition());
	renderComp->draw(window);
}

void GameObject::addComponent(ComponentType compType, std::shared_ptr<IComponent> comp)
{
	if (m_components.find(compType) != m_components.end())
		return;

	m_components.emplace(compType, std::move(comp));
}

void GameObject::removeComponent(ComponentType compType)
{
	if (m_components.find(compType) == m_components.end())
		return;

	m_components.erase(compType);
}
