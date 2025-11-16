#pragma once

#include <string>

#include "Manifold.hpp"
#include "Registry.hpp"

class MissionManager
{
public:
	static MissionManager& getInstance();
	void init(int threshold);
	void processManifold(Manifold manifold);
	bool checkMission();

private:
	int m_inventoryCounter, m_fillCounter, m_missionThreshold;

	MissionManager() = default;
	~MissionManager() = default;
	MissionManager(const MissionManager& rhv) = delete;
	MissionManager& operator =(MissionManager const&) = delete;

	void handleEmptyConsole(int entityID);
	void handleString(int entityID);
};
