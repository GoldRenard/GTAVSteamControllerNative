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

// Here are a natives for 678 build (1.33 online). Yeah, that is only small piece of harmless natives because
// I don't want to contribute to the cheating community. If you such a bad guy, MAKE YOUR OWN.

namespace PLAYER {
    static Player PLAYER_ID() { return NativeInvoke::Invoke<Player>(0xA34E7C2A5118D638); } // 4F8644AF03D0E0D6 8AEA886C
    static Ped PLAYER_PED_ID() { return NativeInvoke::Invoke<Ped>(0xC8B93D94F8954288); } // D80958FC74E988A6 FA92E226
    static BOOL IS_PLAYER_CONTROL_ON(Player player) { return NativeInvoke::Invoke<BOOL, Player>(0x0332C5816E3E66D5, player); } // 49C32D60007AFA47 618857F2
}

namespace UI {
    static BOOL IS_PAUSE_MENU_ACTIVE() { return NativeInvoke::Invoke<BOOL>(0x2BF05095F2389894); } // B0034A223497FFCB D3600591

    static Void _SET_NOTIFICATION_TEXT_ENTRY(char* type) { return NativeInvoke::Invoke<Void, char*>(0x12F4A48D84A3989D, type); } // 202709F4C58A0424 574EE85C
    static Void _ADD_TEXT_COMPONENT_STRING(char* text) { return NativeInvoke::Invoke<Void, char*>(0x2DED6C1306496257, text); } // 6C188BE134E074AA 27A244D8
    static int _DRAW_NOTIFICATION(BOOL blink, BOOL p1) { return NativeInvoke::Invoke<int, BOOL, BOOL>(0xC754466C15BD85AC, blink, p1); } // 2ED7843F8F801023 08F7AF78

    static Void SET_TEXT_FONT(int fontType) { return NativeInvoke::Invoke<Void, int>(0x1F0FA9FF044DCA99, fontType); } // 66E0276CC5F6B9DA 80BC530D
    static Void SET_TEXT_SCALE(float p0, float size) { return NativeInvoke::Invoke<Void, float, float>(0x3990B11991B0B160, p0, size); } // 07C837F9A01C34C9 B6E15B23
    static Void SET_TEXT_COLOUR(int red, int green, int blue, int alpha) { return NativeInvoke::Invoke<Void, int, int, int, int>(0xE626AAE57E9B7B3E, red, green, blue, alpha); } // BE6B23FFA53FB442 E54DD2C8
    static Void SET_TEXT_CENTRE(BOOL align) { return NativeInvoke::Invoke<Void, BOOL>(0xB29CE0BA729EE68B, align); } // C02F4DBFB51D988B E26D39A1
    static Void SET_TEXT_DROPSHADOW(int distance, int r, int g, int b, int a) { return NativeInvoke::Invoke<Void, int, int, int, int, int>(0x0BC95D6E0759A9A3, distance, r, g, b, a); } // 465C84BC39F1C351 E6587517
    static Void SET_TEXT_EDGE(Hash p0, int r, int g, int b, int a) { return NativeInvoke::Invoke<Void, Hash, int, int, int, int>(0xF2C15C6F8F502102, p0, r, g, b, a); } // 441603240D202FA6 3F1A5DAB
    static Void _SET_TEXT_ENTRY(char* text) { return NativeInvoke::Invoke<Void, char*>(0xCF61D472051E607A, text); } // 25FBB336DF1804CB 3E35563E
    static Void _DRAW_TEXT(float x, float y) { return NativeInvoke::Invoke<Void, float, float>(0x0A3C6E0278C7BCEF, x, y); } // CD015E5BB0D96A57 6F8350CE
}

namespace ENTITY {
    static BOOL DOES_ENTITY_EXIST(Entity entity) { return NativeInvoke::Invoke<BOOL, Entity>(0x95CCECA3948CFE7B, entity); } // 7239B21A38F536BA 3AC90869
}

namespace PED {
    static BOOL IS_PED_IN_FLYING_VEHICLE(Ped ped) { return NativeInvoke::Invoke<BOOL, Ped>(0xB93A114562263226, ped); } // 9134873537FA419C CA072485
    static BOOL IS_PED_IN_ANY_VEHICLE(Ped ped, BOOL atGetIn) { return NativeInvoke::Invoke<BOOL, Ped, BOOL>(0x277ECDA23D8CCEB4, ped, atGetIn); } // 997ABD671D25CA0B 3B0171EE
}