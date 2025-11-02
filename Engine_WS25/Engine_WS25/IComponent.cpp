#include "IComponent.h"

int IComponent::s_nextID = 0;

IComponent::IComponent()
	: m_ID(s_nextID++)
{
}