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
#include "controller.h"
#include "log.h"

Controller::Controller() {
    InitSteamController();
}

Controller::~Controller() {}

//-----------------------------------------------------------------------------
// Purpose: callback hook for debug text emitted from the Steam API
//-----------------------------------------------------------------------------
extern "C" void __cdecl SteamAPIDebugTextHook(int nSeverity, const char *pchDebugText) {
    DEBUGOUT(pchDebugText);
}

BOOL InitializeSteam() {
    DEBUGOUT("Initializing SteamAPI...\n");
    // Initialize SteamAPI, if this fails we bail out since we depend on Steam for lots of stuff.
    // You don't necessarily have to though if you write your code to check whether all the Steam
    // interfaces are NULL before using them and provide alternate paths when they are unavailable.
    //
    // This will also load the in-game steam overlay dll into your process.  That dll is normally
    // injected by steam when it launches games, but by calling this you cause it to always load,
    // even when not launched via steam.
    if (!SteamAPI_Init()) {
        DEBUGOUT("SteamAPI_Init() failed\n");
        return FALSE;
    }

    // set our debug handler
    SteamClient()->SetWarningMessageHook(&SteamAPIDebugTextHook);

    // Ensure that the user has logged into Steam. This will always return true if the game is launched
    // from Steam, but if Steam is at the login prompt when you run your game from the debugger, it
    // will return false.
    if (!SteamUser()->BLoggedOn()) {
        DEBUGOUT("Steam user is not logged in\n");
        return FALSE;
    }

    if (!SteamController()->Init()) {
        DEBUGOUT("SteamController()->Init failed.\n");
        return FALSE;
    }
    return TRUE;
}

//-----------------------------------------------------------------------------
// Purpose: Initialize the steam controller actions
//-----------------------------------------------------------------------------
void Controller::InitSteamController() {
    m_ControllerActionSetHandles[ActionSet::Menu] = SteamController()->GetActionSetHandle("Default");
    m_ControllerActionSetHandles[ActionSet::OnFoot] = SteamController()->GetActionSetHandle("Foot");
    m_ControllerActionSetHandles[ActionSet::InVehicle] = SteamController()->GetActionSetHandle("Vehicle");

#ifdef DEBUG
    char text[256];
    sprintf_s(text, "Adding ActionSet Default -> %d", m_ControllerActionSetHandles[ActionSet::Menu]);
    DEBUGOUT(text);
    sprintf_s(text, "Adding ActionSet Foot -> %d", m_ControllerActionSetHandles[ActionSet::OnFoot]);
    DEBUGOUT(text);
    sprintf_s(text, "Adding ActionSet Vehicle -> %d", m_ControllerActionSetHandles[ActionSet::InVehicle]);
    DEBUGOUT(text);
#endif
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
bool Controller::BIsSteamControllerActive() {
    if (m_ActiveControllerHandle) {
        return true;
    }
    return false;
}

void Controller::TriggerHapticPulse() {
    if (BIsSteamControllerActive()) {
        DEBUGOUT("Calling TriggerHapticPulse() for active controller...");
        SteamController()->TriggerHapticPulse(m_ActiveControllerHandle, ESteamControllerPad::k_ESteamControllerPad_Left, 30000);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
// Purpose: Put the controller into a specific action set. Action sets are collections of game-context actions ie "walking", "flying" or "menu"
//-----------------------------------------------------------------------------------------------------------------------------------------------------
void Controller::SetSteamControllerActionSet(ActionSet dwActionSet) {
    if (BIsSteamControllerActive()) {
        // This call is low-overhead and can be called repeatedly from game code that is active in a specific mode.
        SteamController()->ActivateActionSet(m_ActiveControllerHandle, dwActionSet + 1);
    }
}