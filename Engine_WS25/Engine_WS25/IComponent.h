#pragma once

class IComponent
{
public:
	void virtual Update(float deltaTime) = 0;
};
