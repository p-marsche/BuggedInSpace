#pragma once

class IComponent
{
public:
	IComponent();
	virtual ~IComponent() = default;
	int GetID() const { return m_ID; }
	void virtual Update(float deltaTime);

private:
	int m_ID;
	static int s_nextID;
};