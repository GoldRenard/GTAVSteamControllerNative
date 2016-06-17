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

// A handle to the currently active Steam Controller.
ControllerHandle_t Controller::m_ActiveControllerHandle;

// An array of handles to different Steam Controller action set configurations
ControllerActionSetHandle_t Controller::m_ControllerActionSetHandles[eControllerAnalogAction_NumActionSets];

// An array of handles to Steam Controller events that player can bind to controls
ControllerAnalogActionHandle_t Controller::m_ControllerAnalogActionHandles[eControllerAnalogAction_NumActions];

// Origins for all the Steam Controller actions. The 'origin' is where the action is currently bound to,
// ie 'jump' is currently bound to the 'A' button.
EControllerActionOrigin Controller::m_ControllerAnalogActionOrigins[eControllerAnalogAction_NumActions];

BOOL Controller::m_IsNativeActionSets = TRUE;

//-----------------------------------------------------------------------------
// Purpose: Initialize the steam controller api
//-----------------------------------------------------------------------------
BOOL Controller::InitSteamController() {
    if (!SteamController()->Init()) {
        DEBUGOUT(L"SteamController()->Init failed.\n");
        return FALSE;
    }

    for (int i = 0; i <eControllerAnalogAction_NumActions; i++) {
        m_ControllerAnalogActionHandles[i] = 0;
        m_ControllerAnalogActionOrigins[i] = k_EControllerActionOrigin_None;
    }

    m_ControllerAnalogActionHandles[eControllerAnalogAction_Camera] = SteamController()->GetAnalogActionHandle("Camera");
    DEBUGOUT(L"Adding AnalogAction Camera -> %d", m_ControllerAnalogActionHandles[eControllerAnalogAction_Camera]);

    m_ControllerActionSetHandles[eControllerActionSet_Menu] = SteamController()->GetActionSetHandle("Menu");
    m_ControllerActionSetHandles[eControllerActionSet_OnFoot] = SteamController()->GetActionSetHandle("OnFoot");
    m_ControllerActionSetHandles[eControllerActionSet_InVehicle] = SteamController()->GetActionSetHandle("InVehicle");
    m_ControllerActionSetHandles[eControllerActionSet_InFlyingVehicle] = SteamController()->GetActionSetHandle("InFlyingVehicle");

    DEBUGOUT(L"Adding ActionSet Default -> %d", m_ControllerActionSetHandles[eControllerActionSet_Menu]);
    DEBUGOUT(L"Adding ActionSet Foot -> %d", m_ControllerActionSetHandles[eControllerActionSet_OnFoot]);
    DEBUGOUT(L"Adding ActionSet Vehicle -> %d", m_ControllerActionSetHandles[eControllerActionSet_InVehicle]);
    DEBUGOUT(L"Adding ActionSet Flying Vehicle -> %d", m_ControllerActionSetHandles[eControllerActionSet_InFlyingVehicle]);

    for (int i = 0; i < eControllerAnalogAction_NumActionSets; i++) {
        if (m_ControllerActionSetHandles[i] <= 0) {
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
    // Manually call controller frame
    SteamController()->RunFrame();

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
        DEBUGOUT(L"Calling TriggerHapticPulse() for active controller...");
        SteamController()->TriggerHapticPulse(m_ActiveControllerHandle, ESteamControllerPad::k_ESteamControllerPad_Left, 30000);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------------------------------
// Purpose: Put the controller into a specific action set. Action sets are collections of game-context actions ie "walking", "flying" or "menu"
//-----------------------------------------------------------------------------------------------------------------------------------------------------
void Controller::SetSteamControllerActionSet(ECONTROLLERACTIONSET eActionSet) {
    if (IsSteamControllerActive()) {
        SteamController()->ActivateActionSet(m_ActiveControllerHandle, m_IsNativeActionSets
            ? m_ControllerActionSetHandles[eActionSet] : eActionSet + 1);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------------------------
// Purpose: Get the current x,y state of the analog action. Examples of an analog action are a virtual joystick on the trackpad or the real joystick.
//---------------------------------------------------------------------------------------------------------------------------------------------------
BOOL Controller::GetControllerAnalogAction(ECONTROLLERANALOGACTION dwAction, float *x, float *y) {
    if (!IsSteamControllerActive()) {
        *x = 0.0f;
        *y = 0.0f;
        return FALSE;
    }

    ControllerAnalogActionData_t analogData = SteamController()->GetAnalogActionData(m_ActiveControllerHandle, m_ControllerAnalogActionHandles[dwAction]);

    // Actions are only 'active' when they're assigned to a control in an action set, and that action set is active.
    if (analogData.bActive) {
        analogData.x = analogData.x / ANALOG_DATA_RATIO;
        analogData.y = analogData.y / ANALOG_DATA_RATIO;
        *x = analogData.x;
        *y = analogData.y;
    }
    else {
        *x = 0.0f;
        *y = 0.0f;
    }
    return analogData.bActive;
}