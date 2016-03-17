#include "stdafx.h"
#include "script.h"
#include "controller.h"
#include <vector>
#include <map>

ActionSet currentActionSet = ActionSet::Menu;

Controller *controller;

const char* getActionSetName(ActionSet actionSet) {
	return ActionNames[actionSet];
}

#ifdef DEBUG
void draw_state(float x, float y, ActionSet actionSet) {
	char text[256];
	sprintf_s(text, "Controller state: %s", getActionSetName(actionSet));

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

void apply_state(ActionSet actionSet) {
	controller->SetSteamControllerActionSet(actionSet);
#ifdef DEBUG
	draw_state(0.01f, 0.01f, actionSet);
#endif
	if (currentActionSet == actionSet) {
		return;
	}
	currentActionSet = actionSet;
#ifdef DEBUG
	char text[256];
	sprintf_s(text, "Controller state: %s", getActionSetName(actionSet));

	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::_ADD_TEXT_COMPONENT_STRING(text);
	UI::_DRAW_NOTIFICATION(FALSE, FALSE);

	DEBUGOUT(text);

	controller->TriggerHapticPulse();
#endif
}

void handle_state() {
	Player player = PLAYER::PLAYER_ID();
	Ped playerPed = PLAYER::PLAYER_PED_ID();

	if (UI::IS_PAUSE_MENU_ACTIVE() || !ENTITY::DOES_ENTITY_EXIST(playerPed) || !PLAYER::IS_PLAYER_CONTROL_ON(player)) {
		apply_state(ActionSet::Menu);
		return;
	}

	if (PED::IS_PED_IN_ANY_VEHICLE(playerPed, 0)) {
		apply_state(ActionSet::InVehicle);
	}
	else {
		apply_state(ActionSet::OnFoot);
	}
}

void main() {
	if (InitializeSteam()) {
		controller = new Controller();
		while (true) {
			controller->PollSteamController();
			handle_state();
			WAIT(0);
		}
	}
}

void ScriptMain() {
	srand(GetTickCount());
	main();
}