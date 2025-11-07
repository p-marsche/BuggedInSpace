#include "InputComponent.h"
#include "InputManager.h"
#include "VectorUtils.h"
#include <iostream>

InputComponent::InputComponent(int playerNumber)
	: IComponent(ComponentType::Input)
	, m_playerNumber(playerNumber)
	, m_moveInput(0.f, 0.f)
{
	moveInputs.emplace(InputEnum::Up, sf::Vector2f(0.f, -1.f));
	moveInputs.emplace(InputEnum::Left, sf::Vector2f(-1.f, 0.f));
	moveInputs.emplace(InputEnum::Down, sf::Vector2f(0.f, 1.f));
	moveInputs.emplace(InputEnum::Right, sf::Vector2f(1.f, 0.f));
}

void InputComponent::Update(float deltaTime)
{
	m_moveInput = { 0.f, 0.f };
	for (auto& [input, dir] : moveInputs)
	{
		if (InputManager::GetInstance().GetKeyDown(input, m_playerNumber))
			m_moveInput += dir;
	}
	VecUtils::NormalizeVector2f(m_moveInput);
}