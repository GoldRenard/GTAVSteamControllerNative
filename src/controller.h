#pragma once

#include "stdafx.h"
#include "steam/steam_api.h"

#define NUM_ACTION_SETS 3

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

	// Set the current Steam Controller Action set
	void SetSteamControllerActionSet(ActionSet dwActionSet);

	// Return true if there is an active Steam Controller
	bool BIsSteamControllerActive();

	// Find an active Steam controller
	void FindActiveSteamController();

	// Called each frame to update the Steam Controller interface
	void PollSteamController();

	// Initialize the Steam Controller interfaces
	void InitSteamController();

	void TriggerHapticPulse();
private:

	// A handle to the currently active Steam Controller.
	ControllerHandle_t m_ActiveControllerHandle;

	// An array of handles to different Steam Controller action set configurations
	ControllerActionSetHandle_t m_ControllerActionSetHandles[NUM_ACTION_SETS];

};
