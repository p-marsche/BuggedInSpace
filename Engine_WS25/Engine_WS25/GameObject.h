#pragma once

#include <map> 
#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "IComponent.h"
#include "RenderComponent.h"

class GameObject : sf::Transformable
{
public:
	GameObject();
	int GetID() const { return m_ID; }

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	// change to compType-enum templates later
	void AddComponent(std::string compType, std::unique_ptr<IComponent> comp);
	void RemoveComponent(std::string compType);

private:
	int m_ID;
	static int m_nextID;
	std::map <std::string, std::unique_ptr<IComponent> > m_components;

	// placeholder for now
	std::vector<RenderComponent> m_renderComps;
};

