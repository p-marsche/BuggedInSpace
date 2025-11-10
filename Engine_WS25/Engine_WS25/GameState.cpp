#include "pch.h"

#include "GameState.hpp"
#include "GameStateManager.hpp"

void GameState::init(GameStateManager* manager)
{
	m_manager = *manager;
}