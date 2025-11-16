#pragma once

#include <string>

struct Manifold
{
public:
	Manifold(int id1, int id2, std::string tag1, std::string tag2);

	int m_entityID1, m_entityID2;
	std::string m_tag1, m_tag2;
};