#include "stdafx.h"
#include "BaseScript.h"

void BaseScript::Execute() {
    Controller::PollSteamController();

    Player player = PLAYER::PLAYER_ID();
    Ped playerPed = PLAYER::PLAYER_PED_ID();

    if (UI::IS_PAUSE_MENU_ACTIVE() || !ENTITY::DOES_ENTITY_EXIST(playerPed) || !PLAYER::IS_PLAYER_CONTROL_ON(player)) {
        ApplyState(ActionSet::Menu);
    }
    else if (PED::IS_PED_IN_FLYING_VEHICLE(playerPed)) {
        ApplyState(ActionSet::InFlyingVehicle);
    }
    else if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
        ApplyState(ActionSet::InVehicle);
    }
    else {
        ApplyState(ActionSet::OnFoot);
    }
}

void BaseScript::ApplyState(ActionSet dwActionSet) {
    Controller::SetSteamControllerActionSet(dwActionSet);
#if defined (DEBUG) && defined (SCRIPT_ASI)
    RenderState(0.01f, 0.01f, dwActionSet);
#endif
    if (mCurrentActionSet == dwActionSet) {
        return;
    }
    mCurrentActionSet = dwActionSet;
#ifdef DEBUG
    DEBUGOUT(L"Controller state: %s", GetActionSetName(dwActionSet));
    Controller::TriggerHapticPulse();
#ifdef SCRIPT_ASI
    char text[256];
    sprintf_s(text, "Controller state: %s", GetActionSetName(dwActionSet));
    UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
    UI::_ADD_TEXT_COMPONENT_STRING(text);
    UI::_DRAW_NOTIFICATION(FALSE, FALSE);
#endif
#endif
}

void BaseScript::RenderState(float x, float y, ActionSet dwActionSet) {
    char text[256];
    sprintf_s(text, "Controller state: %s", GetActionSetName(dwActionSet));

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