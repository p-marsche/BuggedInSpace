#include "InputComponent.hpp"
#include "InputManager.hpp"
#include "VectorUtils.hpp"

InputComponent::InputComponent(int playerNumber)
	: IComponent(ComponentType::Input)
	, m_playerNumber(playerNumber)
	, m_moveInput(0.f, 0.f)
{
	m_moveInputs.emplace(InputEnum::Up, sf::Vector2f(0.f, -1.f));
	m_moveInputs.emplace(InputEnum::Left, sf::Vector2f(-1.f, 0.f));
	m_moveInputs.emplace(InputEnum::Down, sf::Vector2f(0.f, 1.f));
	m_moveInputs.emplace(InputEnum::Right, sf::Vector2f(1.f, 0.f));
}

void InputComponent::update(float deltaTime)
{
	m_moveInput = { 0.f, 0.f };
	for (auto& [input, dir] : m_moveInputs)
	{
		if (InputManager::getInstance().getKeyDown(input, m_playerNumber))
			m_moveInput += dir;
	}
	VecUtils::normalizeVector2f(m_moveInput);
}
