#include "pch.h"

#include "AiInputComponent.hpp"
#include "GameObject.hpp"
#include "IComponent.hpp"
#include "InputComponent.hpp"
#include "PlayerInputComponent.hpp"
#include "RenderComponent.hpp"
#include "VectorUtils.hpp"

int GameObject::s_nextID = 0;

GameObject::GameObject()
	: m_ID(s_nextID++)
	, m_movespeed(1.f)
{ }

void GameObject::moveObject(sf::Vector2f moveVec)
{
	this->move(moveVec);
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
			movement = { movement.x * m_movespeed, movement.y * m_movespeed };
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

std::shared_ptr<sf::Sprite> GameObject::getSprite()
{
	auto rend = m_components.find(ComponentType::Render);
	if (rend == m_components.end())
		return nullptr;

	auto render = std::dynamic_pointer_cast<RenderComponent>(rend->second);
	return render->getSprite();
}

void GameObject::SetMoveDirection(sf::Vector2f direction)
{
	auto input = m_components.find(ComponentType::Input);
	if (input == m_components.end())
		return;

	auto inputComp = std::dynamic_pointer_cast<AiInputComponent>(input->second);
	VecUtils::normalizeVector2f(direction);
	inputComp->SetMoveDirection(direction);
}

bool GameObject::isShooting()
{
	auto input = m_components.find(ComponentType::Input);
	if (input == m_components.end())
		return false;

	auto inputComp = std::dynamic_pointer_cast<PlayerInputComponent>(input->second);
	return inputComp->isPlayerShooting();
}
