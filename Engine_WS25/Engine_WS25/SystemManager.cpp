#include "pch.h"

#include "SystemManager.hpp"

SystemManager& SystemManager::getInstance()
{ 
	static SystemManager assetManager;
	return assetManager;
}

void SystemManager::init()
{
	
}

void SystemManager::update(float deltaTime)
{
		
}

void SystemManager::render(sf::RenderWindow& window)
{

}