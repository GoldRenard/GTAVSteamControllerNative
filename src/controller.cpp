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

#include "stdafx.h"

//-----------------------------------------------------------------------------
// Purpose: callback hook for debug text emitted from the Steam API
//-----------------------------------------------------------------------------
extern "C" void __cdecl SteamAPIDebugTextHook(int nSeverity, const char *pchDebugText) {
    DEBUGOUT(pchDebugText);
}

// A handle to the currently active Steam Controller.
ControllerHandle_t Controller::m_ActiveControllerHandle;

// An array of handles to different Steam Controller action set configurations
ControllerActionSetHandle_t Controller::m_ControllerActionSetHandles[NUM_ACTION_SETS];

BOOL Controller::m_IsNativeActionSets = TRUE;

//-----------------------------------------------------------------------------
// Purpose: Initialize the steam controller api
//-----------------------------------------------------------------------------
BOOL Controller::InitSteamController() {
    DEBUGOUT("Initializing SteamAPI...\n");
    if (!SteamAPI_Init()) {
        DEBUGOUT("SteamAPI_Init() failed\n");
        return FALSE;
    }

    SteamClient()->SetWarningMessageHook(&SteamAPIDebugTextHook);

    if (!SteamUser()->BLoggedOn()) {
        DEBUGOUT("Steam user is not logged in\n");
        return FALSE;
    }

    if (!SteamController()->Init()) {
        DEBUGOUT("SteamController()->Init failed.\n");
        return FALSE;
    }

    m_ControllerActionSetHandles[ActionSet::Menu] = SteamController()->GetActionSetHandle("Menu");
    m_ControllerActionSetHandles[ActionSet::OnFoot] = SteamController()->GetActionSetHandle("OnFoot");
    m_ControllerActionSetHandles[ActionSet::InVehicle] = SteamController()->GetActionSetHandle("InVehicle");
    m_ControllerActionSetHandles[ActionSet::InFlyingVehicle] = SteamController()->GetActionSetHandle("InFlyingVehicle");

#ifdef DEBUG
    DEBUGOUT("Adding ActionSet Default -> %d", m_ControllerActionSetHandles[ActionSet::Menu]);
    DEBUGOUT("Adding ActionSet Foot -> %d", m_ControllerActionSetHandles[ActionSet::OnFoot]);
    DEBUGOUT("Adding ActionSet Vehicle -> %d", m_ControllerActionSetHandles[ActionSet::InVehicle]);
    DEBUGOUT("Adding ActionSet Flying Vehicle -> %d", m_ControllerActionSetHandles[ActionSet::InFlyingVehicle]);
#endif

    for (int i = 0; i < NUM_ACTION_SETS; i++) {
        if (m_ControllerActionSetHandles[i] <= 0) {
            DEBUGOUT("Wrong IGAS handle detected. Unsupported steam_api.dll version? Anyway, true to use desired values...");
            m_IsNativeActionSets = FALSE;
            break;
        }
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
// Purpose: Called each frame
//-----------------------------------------------------------------------------
void Controller::PollSteamController() {
    // Each frame check our active controller handle
    FindActiveSteamController();
}

//-----------------------------------------------------------------------------
// Purpose: Find an active Steam controller
//-----------------------------------------------------------------------------
void Controller::FindActiveSteamController() {
    // Use the first available steam controller for all interaction. We can call this each frame to handle
    // a controller disconnecting and a different one reconnecting. Handles are guaranteed to be unique for
    // a given controller, even across power cycles.

    // See how many Steam Controllers are active.
    ControllerHandle_t pHandles[STEAM_CONTROLLER_MAX_COUNT];
    int nNumActive = SteamController()->GetConnectedControllers(pHandles);

    // If there's an active controller, and if we're not already using it, select the first one.
    if (nNumActive && (m_ActiveControllerHandle != pHandles[0])) {
        m_ActiveControllerHandle = pHandles[0];
    }

    return;
}

//-----------------------------------------------------------------------------
// Purpose: Return true if there is an active Steam Controller
//-----------------------------------------------------------------------------
BOOL Controller::IsSteamControllerActive() {
    if (m_ActiveControllerHandle) {
        return TRUE;
    }
    return FALSE;
}

void Controller::TriggerHapticPulse() {
    if (IsSteamControllerActive()) {
        DEBUGOUT("Calling TriggerHapticPulse() for active controller...");
        SteamController()->TriggerHapticPulse(m_ActiveControllerHandle, ESteamControllerPad::k_ESteamControllerPad_Left, 30000);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
// Purpose: Put the controller into a specific action set. Action sets are collections of game-context actions ie "walking", "flying" or "menu"
//-----------------------------------------------------------------------------------------------------------------------------------------------------
void Controller::SetSteamControllerActionSet(ActionSet dwActionSet) {
    if (IsSteamControllerActive()) {
        SteamController()->ActivateActionSet(m_ActiveControllerHandle, m_IsNativeActionSets
            ? m_ControllerActionSetHandles[dwActionSet] : dwActionSet + 1);
    }
}