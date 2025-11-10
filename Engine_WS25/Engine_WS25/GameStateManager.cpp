#include "pch.h"

#include "GameState.hpp"
#include "GameStateManager.hpp"

GameStateManager::GameStateManager() : m_currentState(nullptr) {}

void GameStateManager::setState(GameStateEnum name)
{
	if (m_states.find(name) != m_states.end())	//< check if state already exists
	{
		GameState* state = m_states[name];
		if (state != m_currentState)
		{
			if (m_currentState != nullptr)
				m_currentState->exit();
			m_currentState = state;
			m_currentState->init(this);
		}
	}
}

void GameStateManager::registerState(GameStateEnum name, GameState* state)
{
	m_states.try_emplace(name, state);
}
