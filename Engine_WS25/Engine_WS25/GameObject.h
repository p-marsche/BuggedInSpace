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
	void AddComponent(ComponentType compType, std::shared_ptr<IComponent> comp);
	void RemoveComponent(ComponentType compType);

private:
	int m_ID;
	static int m_nextID;
	std::map <ComponentType, std::shared_ptr<IComponent> > m_components;
};

