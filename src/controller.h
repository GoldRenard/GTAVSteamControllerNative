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


#define ANALOG_DATA_RATIO 35


enum ECONTROLLERACTIONSET {
    eControllerActionSet_Menu,
    eControllerActionSet_OnFoot,
    eControllerActionSet_InVehicle,
    eControllerActionSet_InFlyingVehicle,
    eControllerAnalogAction_NumActionSets
};

enum ECONTROLLERANALOGACTION {
    eControllerAnalogAction_Camera,
    eControllerAnalogAction_NumActions
};

class Controller {
public:

    // Initialize the Steam Controller interfaces
    static BOOL InitSteamController();

    // Called each frame to update the Steam Controller interface
    static void PollSteamController();

    // Return true if there is an active Steam Controller
    static BOOL IsSteamControllerActive();

    // Set the current Steam Controller Action set
    static void SetSteamControllerActionSet(ECONTROLLERACTIONSET eActionSet);

    static BOOL GetControllerAnalogAction(ECONTROLLERANALOGACTION eAction, float *x, float *y);

    // Trigger Haptic Pulse (just for debugging)
    static void TriggerHapticPulse();
private:

    // A handle to the currently active Steam Controller.
    static ControllerHandle_t m_ActiveControllerHandle;

    // Check whether is we got action sets by their name or we should use them by index
    static BOOL m_IsNativeActionSets;

    // An array of handles to different Steam Controller action set configurations
    static ControllerActionSetHandle_t m_ControllerActionSetHandles[eControllerAnalogAction_NumActionSets];

    // An array of handles to Steam Controller events that player can bind to controls
    static ControllerAnalogActionHandle_t m_ControllerAnalogActionHandles[eControllerAnalogAction_NumActions];

    // Origins for all the Steam Controller actions. The 'origin' is where the action is currently bound to,
    // ie 'jump' is currently bound to the 'A' button.
    static EControllerActionOrigin m_ControllerAnalogActionOrigins[eControllerAnalogAction_NumActions];
};
