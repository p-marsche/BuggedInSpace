#include "pch.h"

#include "Entity.hpp"

int Entity::s_nextID = 0;

Entity::Entity()
	: m_ID(s_nextID++)
{
}
