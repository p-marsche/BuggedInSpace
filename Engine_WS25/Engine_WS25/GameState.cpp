#include "pch.h"

#include "GameState.hpp"
#include "GameStateManager.hpp"

GameState::GameState() : m_manager(nullptr) {}

void GameState::init(GameStateManager* manager)
{
	m_manager = manager;
	this->run();
}

void GameState::changeState(GameStateEnum state) const
{
	if(m_manager)
		m_manager->setState(state);
}