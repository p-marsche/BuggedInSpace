#include "pch.h"

#include "AiInputComponent.hpp"

AiInputComponent::AiInputComponent()
{ }

void AiInputComponent::SetMoveDirection(sf::Vector2f direction)
{
	m_moveInput = direction;
}
