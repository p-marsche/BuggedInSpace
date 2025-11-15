#include "pch.h"

#include "RenderComponent.hpp"

//higher zIndex = further up front
RenderComponent::RenderComponent(int entityID, sf::Texture& texture, bool visible,
	int zIndex, sf::Vector2f scale)
	: IComponent(entityID)
	, m_isVisible(visible)
	, m_zIndex(zIndex)
{
	m_sprite = sf::Sprite(texture);
	m_sprite.setScale(scale);
	m_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}
