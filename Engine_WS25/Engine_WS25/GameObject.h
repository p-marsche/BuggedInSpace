#pragma once

#include <map> 
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "IComponent.h"

class GameObject : sf::Transformable
{
public:
	GameObject();
	int GetID() { return m_ID; }

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void AddComponent(std::string compType, IComponent* comp);
	void RemoveComponent(std::string compType);

private:
	int m_ID;
	static int m_nextID;
	std::map <std::string, std::unique_ptr<IComponent> > m_components;
};

