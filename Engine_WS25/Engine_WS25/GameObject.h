#pragma once

#include <unordered_map> 
#include <vector>
#include <string>
#include <memory>

#include <SFML/Graphics.hpp>

#include "IComponent.h"
#include "RenderComponent.h"
#include "InputComponent.h"

class GameObject : sf::Transformable
{
public:
	GameObject();
	int getID() const { return m_ID; }
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void addComponent(ComponentType compType, std::shared_ptr<IComponent> comp);
	void removeComponent(ComponentType compType);

private:
	static int s_nextID;

	int m_ID;
	std::unordered_map <ComponentType, std::shared_ptr<IComponent> > m_components;
};
