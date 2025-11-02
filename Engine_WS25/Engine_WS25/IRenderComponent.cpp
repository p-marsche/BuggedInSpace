#include "IRenderComponent.h"

IRenderComponent::IRenderComponent(sf::Texture texture)
{
	m_sprite = sf::Sprite(texture);
}

void IRenderComponent::Update(float deltaTime) 
{
	// animation stuff here
	return;
}

void IRenderComponent::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void IRenderComponent::SetSpritePosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}
