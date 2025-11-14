#include "pch.h"

#include "RenderComponent.hpp"

// change to work with shared_ptr<Texture> and/or with Spritesheet instead?
RenderComponent::RenderComponent(int entityID, sf::Texture& texture, bool visible)
	: IComponent(entityID)
	, m_isVisible(visible)
{
	m_sprite = sf::Sprite(texture);
	m_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}
