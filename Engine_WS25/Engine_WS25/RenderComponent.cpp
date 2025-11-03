#include "RenderComponent.h"

RenderComponent::RenderComponent(sf::Texture& texture)
	: m_sprite(texture)
{
}

void RenderComponent::Update(float deltaTime) 
{
	// animation stuff here?
	return;
}

void RenderComponent::Draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void RenderComponent::SetSpritePosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}
