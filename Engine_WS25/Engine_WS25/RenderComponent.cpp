#include "RenderComponent.h"

// change to work with shared_ptr<Texture> and/or with Spritesheet instead?
RenderComponent::RenderComponent(sf::Texture& texture)
	: m_sprite(texture)
	, IComponent(ComponentType::Render)
{
	m_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}

void RenderComponent::update(float deltaTime) 
{
	// animation stuff here?
	return;
}

void RenderComponent::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void RenderComponent::setSpritePosition(sf::Vector2f position)
{
	m_sprite.setPosition(position);
}
