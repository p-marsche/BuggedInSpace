#include "IComponent.h"

int IComponent::s_nextID = 0;

IComponent::IComponent(ComponentType compType)
	: m_ID(s_nextID++),
	m_compType(compType)
{
}