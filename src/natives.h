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

// Here are a natives for v1.0.1011.1 build. Yeah, that is only small piece of harmless natives because
// I don't want to contribute to the cheating community. If you such a bad guy, BURN IN HELL.

namespace PLAYER {
    static Player PLAYER_ID() { return NativeInvoke::Invoke<Player>(0xBE369BE1BC57A796); } // 4F8644AF03D0E0D6 8AEA886C
    static Ped PLAYER_PED_ID() { return NativeInvoke::Invoke<Ped>(0x17B5CC8A8615737D); } // D80958FC74E988A6 FA92E226
    static BOOL IS_PLAYER_CONTROL_ON(Player player) { return NativeInvoke::Invoke<BOOL, Player>(0x94A5DEE82C898FDF, player); } // 49C32D60007AFA47 618857F2
}

namespace VEHICLE {
    static Ped GET_PED_IN_VEHICLE_SEAT(Vehicle vehicle, int index) { return NativeInvoke::Invoke<Ped, Vehicle, int>(0x17206B315923243C, vehicle, index); } // BB40DD2270B65366 388FDE9A
}

namespace UI {
    static BOOL IS_PAUSE_MENU_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0x95DBE123BC2DB80B); } // B0034A223497FFCB D3600591
    static Void _SET_NOTIFICATION_TEXT_ENTRY(char* type) { return NativeInvoke::Invoke<Void, char*>(0xBD18006F0815A298, type); } // 202709F4C58A0424 574EE85C
    // NON-EXITST?
    static Void _ADD_TEXT_COMPONENT_STRING(char* text) { return NativeInvoke::Invoke<Void, char*>(0xDA35BDB37E728640, text); } // 6C188BE134E074AA 27A244D8
    static int _DRAW_NOTIFICATION(BOOL blink, BOOL p1) { return NativeInvoke::Invoke<int, BOOL, BOOL>(0x23048DD0C6E21613, blink, p1); } // 2ED7843F8F801023 08F7AF78
}

namespace ENTITY {
    static BOOL DOES_ENTITY_EXIST(Entity entity) { return NativeInvoke::Invoke<BOOL, Entity>(0x23E9113C762466ED, entity); } // 7239B21A38F536BA 3AC90869
}

namespace PED {
    static BOOL IS_PED_IN_FLYING_VEHICLE(Ped ped) { return NativeInvoke::Invoke<BOOL, Ped>(0xE1EB864800193FC8, ped); } // 9134873537FA419C CA072485
    static BOOL IS_PED_IN_ANY_VEHICLE(Ped ped, BOOL atGetIn) { return NativeInvoke::Invoke<BOOL, Ped, BOOL>(0xFD0FE723227D5AB6, ped, atGetIn); } // 997ABD671D25CA0B 3B0171EE
    static BOOL IS_PED_SITTING_IN_ANY_VEHICLE(Ped ped) { return NativeInvoke::Invoke<BOOL, Ped>(0xD035C652F0986F10, ped); } // 826AA586EDB9FEF8 0EA9CA03
    static Vehicle GET_VEHICLE_PED_IS_IN(Ped ped, BOOL getLastVehicle) { return NativeInvoke::Invoke<Vehicle, Ped, BOOL>(0x60604E51E30D25B8, ped, getLastVehicle); } // 9A9112A0FE9A4713 AFE92319
}

namespace CONTROLS {
    static BOOL _SET_CONTROL_NORMAL(int inputGroup, int control, float amount) { return NativeInvoke::Invoke<BOOL, int, int, float>(0x09EC89E3937B74EE, inputGroup, control, amount); } // E8A25867FBA3B05E
    static Void DISABLE_CONTROL_ACTION(int inputGroup, int control, BOOL disable) { return NativeInvoke::Invoke<Void, int, int, BOOL>(0xD1BB2AD73E7FC3A7, inputGroup, control, disable); } // FE99B66D079CF6BC 3800C0DC
}