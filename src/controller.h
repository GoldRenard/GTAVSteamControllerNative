// ======================================================================
// STEAM CONTROLLER NATIVE FOR GRAND THEFT AUTO V
// Copyright (C) 2016 Ilya Egorov (goldrenard@gmail.com)

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ======================================================================

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
