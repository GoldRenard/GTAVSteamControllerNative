#pragma once

#include "stdafx.h"
#include "steam/steam_api.h"

BOOL InitializeSteam();

enum ActionSet {
	Menu = 0,
	OnFoot = 1,
	InVehicle = 2
};

static const char* ActionNames[] = { "Menu", "OnFoot", "InVehicle" };

class Controller {
public:
	Controller();
	~Controller();

	// Return true if there is an active Steam Controller
	bool BIsSteamControllerActive();

	// Find an active Steam controller
	void FindActiveSteamController();

	// Called each frame to update the Steam Controller interface
	void PollSteamController();

	void TriggerHapticPulse();
private:

	// A handle to the currently active Steam Controller.
	ControllerHandle_t m_ActiveControllerHandle;
};
