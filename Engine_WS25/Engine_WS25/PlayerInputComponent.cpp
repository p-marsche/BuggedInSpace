#include "pch.h"

#include "InputManager.hpp"
#include "PlayerInputComponent.hpp"
#include "VectorUtils.hpp"


PlayerInputComponent::PlayerInputComponent(int playerNumber)
	: m_playerNumber(playerNumber)
{ }

void PlayerInputComponent::update(float deltaTime)
{
	m_moveInput = { 0.f, 0.f };
	for (auto& [input, dir] : m_moveInputs)
	{
		if (InputManager::getInstance().getKeyDown(input, m_playerNumber))
			m_moveInput += dir;
	}
	VecUtils::normalizeVector2f(m_moveInput);
}
