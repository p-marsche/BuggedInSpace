#pragma once

#include "ComponentTypeEnum.hpp"

class IComponent;

class GameObject : sf::Transformable
{
public:
	GameObject();
	int getID() const { return m_ID; }
	void moveObject(sf::Vector2f moveVec);
	sf::Vector2f getObjectPosition() { return this->getPosition(); }
	std::shared_ptr<sf::Sprite> getSprite();
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void addComponent(ComponentType compType, std::shared_ptr<IComponent> comp);
	void removeComponent(ComponentType compType);

private:
	static int s_nextID;

	int m_ID;
	std::unordered_map <ComponentType, std::shared_ptr<IComponent> > m_components;
};
