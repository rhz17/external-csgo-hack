#pragma once

#include "../shared/slim.h"

namespace var {
	// memory
	SlimUtils::SlimMem mem = { };
	DWORD pid = { };

	// enemy
	DWORD EnemyPlayer = { }; // enemy on crosshair
	int EnemyHealth = { }; // enemy health
	int EnemyTeam = { }; // enemy team

	// local
	DWORD LocalPlayer = { }; // local player
	int LocalHealth = { }; // local player health
	int LocalTeam = { }; // local player team
	int CrosshairID = { }; // local player crosshir

	// hacks values
	struct config {
		int trigger_delay = 100;
	} config;
}