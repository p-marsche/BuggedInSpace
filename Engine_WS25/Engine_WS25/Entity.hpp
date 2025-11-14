#pragma once

struct Entity
{
public:
	Entity();

	int m_ID;

private:
	static int s_nextID;
};
