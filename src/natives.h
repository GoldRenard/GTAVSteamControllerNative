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

// Here are a natives for 1.0.791.2 build (1.35 online). Yeah, that is only small piece of harmless natives because
// I don't want to contribute to the cheating community. If you such a bad guy, BURN IN HELL.

namespace PLAYER {
    static Player PLAYER_ID() { return NativeInvoke::Invoke<Player>(0xE0BDAFA1A39552D6); } // 4F8644AF03D0E0D6 8AEA886C
    static Ped PLAYER_PED_ID() { return NativeInvoke::Invoke<Ped>(0x06736567F820A39E); } // D80958FC74E988A6 FA92E226
    static BOOL IS_PLAYER_CONTROL_ON(Player player) { return NativeInvoke::Invoke<BOOL, Player>(0x6F54F6E4D3F3FD07, player); } // 49C32D60007AFA47 618857F2
}

namespace VEHICLE {
    static Ped GET_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int index) { return NativeInvoke::Invoke<Ped, Vehicle, int>(0x4321FC7479614822, vehicle, index); } // BB40DD2270B65366 388FDE9A
}

namespace UI {
    static BOOL IS_PAUSE_MENU_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0x3DC360442A11BB38); } // B0034A223497FFCB D3600591
    static Void _SET_NOTIFICATION_TEXT_ENTRY(char* type) { return NativeInvoke::Invoke<Void, char*>(0x999E5F6D1B49D87B, type); } // 202709F4C58A0424 574EE85C
    static Void _ADD_TEXT_COMPONENT_STRING(char* text) { return NativeInvoke::Invoke<Void, char*>(0x9C174A0D56FFB64A, text); } // 6C188BE134E074AA 27A244D8
    static int _DRAW_NOTIFICATION(BOOL blink, BOOL p1) { return NativeInvoke::Invoke<int, BOOL, BOOL>(0xB452F88B6A7B058D, blink, p1); } // 2ED7843F8F801023 08F7AF78
}

namespace ENTITY {
    static BOOL DOES_ENTITY_EXIST(Entity entity) { return NativeInvoke::Invoke<BOOL, Entity>(0xC1EDB61CE0A4B94E, entity); } // 7239B21A38F536BA 3AC90869
}

namespace PED {
    static BOOL IS_PED_IN_FLYING_VEHICLE(Ped ped) { return NativeInvoke::Invoke<BOOL, Ped>(0x211EB61B2F3222D0, ped); } // 9134873537FA419C CA072485
    static BOOL IS_PED_IN_ANY_VEHICLE(Ped ped, BOOL atGetIn) { return NativeInvoke::Invoke<BOOL, Ped, BOOL>(0x0FDFEC0DD29106EE, ped, atGetIn); } // 997ABD671D25CA0B 3B0171EE
    static BOOL IS_PED_SITTING_IN_ANY_VEHICLE(Ped ped) { return NativeInvoke::Invoke<BOOL, Ped>(0x7A6749CADAC50206, ped); } // 826AA586EDB9FEF8 0EA9CA03
    static Vehicle GET_VEHICLE_PED_IS_IN(Ped ped, BOOL getLastVehicle) { return NativeInvoke::Invoke<Vehicle, Ped, BOOL>(0x34E1EF1E8BCD1BFC, ped, getLastVehicle); } // 9A9112A0FE9A4713 AFE92319
}

namespace CONTROLS {
    static BOOL _SET_CONTROL_NORMAL(int inputGroup, int control, float amount) { return NativeInvoke::Invoke<BOOL, int, int, float>(0x1785FD24F6556E21, inputGroup, control, amount); } // E8A25867FBA3B05E 
    static Void DISABLE_CONTROL_ACTION(int inputGroup, int control, BOOL disable) { return NativeInvoke::Invoke<Void, int, int, BOOL>(0xC80D2B3478FFF428, inputGroup, control, disable); } // FE99B66D079CF6BC 3800C0DC
}

namespace CAM {
    static BOOL IS_GAMEPLAY_CAM_RENDERING() { return NativeInvoke::Invoke<BOOL>(0x611B1E292F714CAD); } // 39B5D1B10383F0C8 0EF276DA
    static int GET_FOLLOW_PED_CAM_VIEW_MODE() { return NativeInvoke::Invoke<int>(0x8DC3C8E197F6A40D); } // 8D4D46230B2C353A A65FF946
    static float GET_GAMEPLAY_CAM_RELATIVE_HEADING() { return NativeInvoke::Invoke<float>(0x636C4DCA04BD0ED0); } // 743607648ADD4587 CAF839C2
    static Void SET_GAMEPLAY_CAM_RELATIVE_HEADING(float heading) { return NativeInvoke::Invoke<Void, float>(0x086A554C80BC6C5D, heading); } // B4EC2312F4E5B1F1 20C6217C
    static float GET_GAMEPLAY_CAM_RELATIVE_PITCH() { return NativeInvoke::Invoke<float>(0xE9523E9DA35E0C2F); } // 3A6867B4845BEDA2 FC5A4946
    static Void SET_GAMEPLAY_CAM_RELATIVE_PITCH(float x, float Value2) { return NativeInvoke::Invoke<Void, float, float>(0xA71476EEBE45FF73, x, Value2); } // 6D0858B8EDFD2B7D 6381B963
    static Void _SET_GAMEPLAY_CAM_RAW_YAW(float yaw) { return NativeInvoke::Invoke<Void, float>(0x0D236E8B463D43B9, yaw); } // 103991D4A307D472 
    static Void _SET_GAMEPLAY_CAM_RAW_PITCH(float pitch) { return NativeInvoke::Invoke<Void, float>(0x871B8143363B3898, pitch); } // 759E13EBC1C15C5A 
}