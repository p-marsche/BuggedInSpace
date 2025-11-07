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
	int GetID() const { return m_ID; }

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);

	void AddComponent(ComponentType compType, std::shared_ptr<IComponent> comp);
	void RemoveComponent(ComponentType compType);

private:
	int m_ID;
	static int m_nextID;
	std::unordered_map <ComponentType, std::shared_ptr<IComponent> > m_components;
};

