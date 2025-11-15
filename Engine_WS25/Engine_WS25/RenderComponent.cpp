#include "pch.h"

#include "RenderComponent.hpp"

/// <summary>
/// Rendercomp-Constructor
/// </summary>
/// <param name="entityID"></param>
/// <param name="texture"></param>
/// <param name="visible"></param>
/// <param name="zIndex"> higher = further up front </param>
RenderComponent::RenderComponent(int entityID, sf::Texture& texture, bool visible, int zIndex)
	: IComponent(entityID)
	, m_isVisible(visible)
	, m_zIndex(zIndex)
{
	m_sprite = sf::Sprite(texture);
	m_sprite.setOrigin(texture.getSize().x / 2.f, texture.getSize().y / 2.f);
}
