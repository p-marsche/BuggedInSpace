#pragma once

#include "ComponentTypeEnum.hpp"

class IComponent;

class GameObject : sf::Transformable
{
public:
	GameObject();
	int getID() const { return m_ID; }
	void setMovespeed(int speed) { m_movespeed = speed; }
	sf::Vector2f getObjectPosition() { return this->getPosition(); }
	void update(float deltaTime);
	void draw(sf::RenderWindow& window);
	void addComponent(ComponentType compType, std::shared_ptr<IComponent> comp);
	void removeComponent(ComponentType compType);
	void moveObject(sf::Vector2f moveVec);

	// refactor later, maybe use get-component to get shared_ptr?
	std::shared_ptr<sf::Sprite> getSprite();
	void SetMoveDirection(sf::Vector2f direction);
	bool isShooting();


private:
	static int s_nextID;

	int m_ID;
	float m_movespeed;
	std::unordered_map <ComponentType, std::shared_ptr<IComponent> > m_components;
};
