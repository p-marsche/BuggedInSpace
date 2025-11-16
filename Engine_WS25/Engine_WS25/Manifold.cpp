#include "pch.h"

#include "Manifold.hpp"

Manifold::Manifold(int id1, int id2, std::string tag1, std::string tag2)
	: m_entityID1(id1)
	, m_entityID2(id2)
	, m_tag1(tag1)
	, m_tag2(tag2)
{ }