#include "pch.h"

#include "GameState.hpp"

void GameState::init(GameStateManager* manager)
{
	m_manager = *manager;
}