#include "pch.h"

#include "InputComponent.hpp"
#include "InputManager.hpp"
#include "VectorUtils.hpp"

InputComponent::InputComponent()
	: IComponent(ComponentType::Input)
	, m_moveInput(0.f, 0.f)
{
	m_moveInputs.emplace(InputEnum::Up, sf::Vector2f(0.f, -1.f));
	m_moveInputs.emplace(InputEnum::Left, sf::Vector2f(-1.f, 0.f));
	m_moveInputs.emplace(InputEnum::Down, sf::Vector2f(0.f, 1.f));
	m_moveInputs.emplace(InputEnum::Right, sf::Vector2f(1.f, 0.f));
}
