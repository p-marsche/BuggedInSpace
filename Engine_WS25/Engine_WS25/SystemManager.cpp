#include "pch.h"

#include "SystemManager.hpp"
#include "PhysicsSystem.hpp"
#include "PlayerInputSystem.hpp"
#include "RenderSystem.hpp"
//#include "HealthSystem.hpp"

SystemManager& SystemManager::getInstance()
{ 
	static SystemManager assetManager;
	return assetManager;
}

void SystemManager::init()
{
	auto physics = std::make_shared<PhysicsSystem>();
	m_systems.insert({ SystemType::Physics, physics });
	auto input = std::make_shared<PlayerInputSystem>();
	m_systems.insert({ SystemType::PlayerInput, input });
	auto render = std::make_shared<RenderSystem>();
	m_systems.insert({ SystemType::Render, render });

	//auto health = std::make_shared<HealthSystem>();
	//m_systems.insert({ SystemType::Health, health });

}

void SystemManager::update(float deltaTime)
{
	m_systems.at(SystemType::PlayerInput)->update(deltaTime);
	m_systems.at(SystemType::Physics)->update(deltaTime);
	m_systems.at(SystemType::Render)->update(deltaTime);
}

void SystemManager::render(sf::RenderWindow& window)
{
	std::shared_ptr<RenderSystem> rendSys =
		std::dynamic_pointer_cast<RenderSystem>(m_systems.at(SystemType::Render));

	rendSys->render(window);
}