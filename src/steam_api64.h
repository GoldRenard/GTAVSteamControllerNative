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

#define S_CALLTYPE __cdecl

typedef unsigned __int32 uint32;

typedef void        (S_CALLTYPE *VOIDPROC)();
typedef bool        (S_CALLTYPE *BOOLPROC)();
typedef bool        (S_CALLTYPE *RSTPROC)(uint32 unOwnAppID);
typedef void        (S_CALLTYPE *REGPROC)(INT_PTR pCallback, int iCallback);
typedef void        (S_CALLTYPE *UNREGPROC)(INT_PTR pCallback);
typedef INT_PTR     (S_CALLTYPE *APIPROC)();

typedef ISteamController003* (S_CALLTYPE *CONTROLLERPROC)();

struct steam_api64_dll {
    HMODULE dll;
    BOOLPROC SteamAPI_Init;
    VOIDPROC SteamAPI_Shutdown;
    RSTPROC SteamAPI_RestartAppIfNecessary;
    REGPROC SteamAPI_RegisterCallback;
    UNREGPROC SteamAPI_UnregisterCallback;
    VOIDPROC SteamAPI_RunCallbacks;

    APIPROC SteamApps;
    APIPROC SteamUserStats;
    APIPROC SteamUtils;
    APIPROC SteamUser;
    APIPROC SteamFriends;
    CONTROLLERPROC SteamController;

    void PrintPointer(const char* procName, INT_PTR ptr) {
        DEBUGOUT("%s() = [0x%I64X]", procName, ptr);
    }

    void PrintPointers() {
        PrintPointer("SteamAPI_Init", (INT_PTR) SteamAPI_Init);
        PrintPointer("SteamAPI_Shutdown", (INT_PTR) SteamAPI_Shutdown);
        PrintPointer("SteamAPI_RestartAppIfNecessary", (INT_PTR) SteamAPI_RestartAppIfNecessary);
        PrintPointer("SteamAPI_RegisterCallback", (INT_PTR) SteamAPI_RegisterCallback);
        PrintPointer("SteamAPI_UnregisterCallback", (INT_PTR) SteamAPI_UnregisterCallback);
        PrintPointer("SteamAPI_RunCallbacks", (INT_PTR) SteamAPI_RunCallbacks);
        PrintPointer("SteamApps", (INT_PTR) SteamApps);
        PrintPointer("SteamUserStats", (INT_PTR) SteamUserStats);
        PrintPointer("SteamUtils", (INT_PTR) SteamUtils);
        PrintPointer("SteamUser", (INT_PTR) SteamUser);
        PrintPointer("SteamFriends", (INT_PTR) SteamFriends);
        PrintPointer("SteamController", (INT_PTR) SteamController);
    }
} static steam_api64;

void S_CALLTYPE SteamAPI_InitProxy();

void S_CALLTYPE SteamAPI_CloseProxy();

bool S_CALLTYPE _SteamAPI_Init();

void S_CALLTYPE _SteamAPI_Shutdown();

bool S_CALLTYPE _SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID);

void S_CALLTYPE _SteamAPI_RegisterCallback(INT_PTR pCallback, int iCallback);

void S_CALLTYPE _SteamAPI_UnregisterCallback(INT_PTR pCallback);

void S_CALLTYPE _SteamAPI_RunCallbacks();

/*
    GTA V Expects:      STEAMAPPS_INTERFACE_VERSION006
    Latest SDK 1.36:    STEAMAPPS_INTERFACE_VERSION007
*/
INT_PTR S_CALLTYPE _SteamApps();

/* GTA V Expects actual version (STEAMUSERSTATS_INTERFACE_VERSION011). */
INT_PTR S_CALLTYPE _SteamUserStats();

/*
    GTA V Expects:      SteamUtils006
    Latest SDK 1.36:    SteamUtils007
*/
INT_PTR S_CALLTYPE _SteamUtils();

/*
    GTA V Expects:      SteamUser017
    Latest SDK 1.36:    SteamUser018
*/
INT_PTR S_CALLTYPE _SteamUser();

/*
    GTA V Expects:      SteamFriends014
    Latest SDK 1.36:    SteamFriends015
*/
INT_PTR S_CALLTYPE _SteamFriends();

/*
    GTA V Expects:      Ha! It doesn't even expect it. Surprise!
    Latest SDK 1.36:    SteamController003
*/
ISteamController003 *SteamController();