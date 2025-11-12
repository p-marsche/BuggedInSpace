#include "pch.h"

#include "InputManager.hpp"
#include "PlayerInputComponent.hpp"
#include "VectorUtils.hpp"


PlayerInputComponent::PlayerInputComponent(int playerNumber)
	: m_playerNumber(playerNumber)
	, m_shooting(false)
	, m_fireCooldown(1.5f)
	, m_timeSinceShot(1.5f)
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

	// only check player shooting intention IF cooldown is elapsed fully
	if (m_timeSinceShot < m_fireCooldown)
	{
		m_shooting = false;
		m_timeSinceShot += deltaTime;
	}
	else if (InputManager::getInstance().getKeyDown(InputEnum::Shoot, m_playerNumber))
	{
		m_timeSinceShot = 0.f;
		m_shooting = true;
	}
}
