#include "InputComponent.h"

InputComponent::InputComponent(int playerNumber)
	: m_playerNumber(playerNumber),
	IComponent(ComponentType::Input)
{
	// switch for respective input polls here
}