#include "stdafx.h"
#include "BaseScript.h"

void DisableRecordingControls() {
    CONTROLS::DISABLE_CONTROL_ACTION(0, ControlReplayStartStopRecording, true);
    CONTROLS::DISABLE_CONTROL_ACTION(0, ControlReplayStartStopRecordingSecondary, true);
    CONTROLS::DISABLE_CONTROL_ACTION(0, ControlReplayRecord, true);
    CONTROLS::DISABLE_CONTROL_ACTION(0, ControlReplaySave, true);
}

BOOL IsDriver(Ped pPlayer) {
    Vehicle pVehicle = PED::GET_VEHICLE_PED_IS_IN(pPlayer, FALSE);
    return pVehicle ? pPlayer == VEHICLE::GET_PED_IN_VEHICLE_SEAT(pVehicle, -1) : FALSE;
}

void BaseScript::Execute() {
    DisableRecordingControls();
    Controller::PollSteamController();

    Player player = PLAYER::PLAYER_ID();
    Ped playerPed = PLAYER::PLAYER_PED_ID();

    if (UI::IS_PAUSE_MENU_ACTIVE() 
        || PED::IS_PED_DEAD_OR_DYING(playerPed, TRUE) 
        || !ENTITY::DOES_ENTITY_EXIST(playerPed) 
        || !PLAYER::IS_PLAYER_CONTROL_ON(player)) {
        ApplyState(eControllerActionSet_Menu);
    }
    else if (PED::IS_PED_IN_FLYING_VEHICLE(playerPed) && IsDriver(playerPed)) {
        ApplyState(eControllerActionSet_InFlyingVehicle);
    }
    else if ((PED::IS_PED_IN_ANY_VEHICLE(playerPed, FALSE) || PED::IS_PED_SITTING_IN_ANY_VEHICLE(playerPed)) && IsDriver(playerPed)) {
        ApplyState(eControllerActionSet_InVehicle);
    }
    else {
        ApplyState(eControllerActionSet_OnFoot);
    }
}

void BaseScript::ApplyState(ECONTROLLERACTIONSET eActionSet) {
    Controller::SetSteamControllerActionSet(eActionSet);
#if defined (DEBUG) && defined (SCRIPT_ASI)
    RenderState(0.01f, 0.01f, eActionSet);
#endif
    if (mCurrentActionSet == eActionSet) {
        return;
    }
    mCurrentActionSet = eActionSet;
#ifdef DEBUG
    DEBUGOUT(L"Controller state: %s", GetActionSetName(eActionSet));
    Controller::TriggerHapticPulse();

    char text[256];
    const char* name = GetActionSetNameA(eActionSet);
    sprintf_s(text, "Controller state: %s", name);
    delete[] name;
    UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
    UI::_ADD_TEXT_COMPONENT_STRING(text);
    UI::_DRAW_NOTIFICATION(FALSE, FALSE);
#endif
}

#if defined (DEBUG) && defined (SCRIPT_ASI)
void BaseScript::RenderState(float x, float y, ECONTROLLERACTIONSET eActionSet) {
    char text[256];

    float x1, y1;
    Controller::GetControllerAnalogAction(eControllerAnalogAction_Camera, &x1, &y1);
    float x2 = CONTROLS::GET_CONTROL_NORMAL(0, ControlLookUpDown);
    float y2 = CONTROLS::GET_CONTROL_NORMAL(0, ControlLookLeftRight);

    const char* name = GetActionSetNameA(eActionSet);
    sprintf_s(text, "Controller state: %s | Analog: X=%.2f Y=%.2f | Game: X=%.2f Y=%.2f", name, x1, y1, x2, y2);
    delete[] name;

    UI::SET_TEXT_FONT(0);
    UI::SET_TEXT_SCALE(0.0, 0.20);
    UI::SET_TEXT_COLOUR(255, 255, 255, 255);
    UI::SET_TEXT_CENTRE(0);
    UI::SET_TEXT_DROPSHADOW(0, 0, 0, 0, 0);
    UI::SET_TEXT_EDGE(1, 0, 0, 0, 205);
    UI::_SET_TEXT_ENTRY("STRING");
    UI::_ADD_TEXT_COMPONENT_STRING(text);
    UI::_DRAW_TEXT(x, y);
}
#endif