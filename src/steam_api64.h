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

typedef void        (S_CALLTYPE *VOIDPROC)();
typedef bool        (S_CALLTYPE *BOOLPROC)();
typedef bool        (S_CALLTYPE *RSTPROC)(uint32 unOwnAppID);
typedef void        (S_CALLTYPE *REGPROC)(INT_PTR pCallback, int iCallback);
typedef void        (S_CALLTYPE *UNREGPROC)(INT_PTR pCallback);
typedef INT_PTR(S_CALLTYPE *APIPROC)();
typedef HSteamUser(S_CALLTYPE *HUSERPROC)();
typedef HSteamPipe(S_CALLTYPE *HPIPEPROC)();

typedef ISteamController003*    (S_CALLTYPE *CONTROLLERPROC)();
typedef ISteamClient017*        (S_CALLTYPE *CLIENTPROC)();

static void PrintPointer(const WCHAR* procName, INT_PTR ptr) {
    DEBUGOUT(L"%s() = [0x%I64X]", procName, ptr);
}

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
    CLIENTPROC SteamClient;
    CONTROLLERPROC SteamController;

    HPIPEPROC GetHSteamPipe;
    HUSERPROC GetHSteamUser;

    void PrintPointers() {
        DEBUGOUT(L"Proxy function pointers:");
        PrintPointer(L"SteamAPI_Init", (INT_PTR) SteamAPI_Init);
        PrintPointer(L"SteamAPI_Shutdown", (INT_PTR) SteamAPI_Shutdown);
        PrintPointer(L"SteamAPI_RestartAppIfNecessary", (INT_PTR) SteamAPI_RestartAppIfNecessary);
        PrintPointer(L"SteamAPI_RegisterCallback", (INT_PTR) SteamAPI_RegisterCallback);
        PrintPointer(L"SteamAPI_UnregisterCallback", (INT_PTR) SteamAPI_UnregisterCallback);
        PrintPointer(L"SteamAPI_RunCallbacks", (INT_PTR) SteamAPI_RunCallbacks);
        PrintPointer(L"SteamApps", (INT_PTR) SteamApps);
        PrintPointer(L"SteamUserStats", (INT_PTR) SteamUserStats);
        PrintPointer(L"SteamUtils", (INT_PTR) SteamUtils);
        PrintPointer(L"SteamUser", (INT_PTR) SteamUser);
        PrintPointer(L"SteamFriends", (INT_PTR) SteamFriends);
        PrintPointer(L"SteamClient", (INT_PTR) SteamClient);
        PrintPointer(L"SteamController", (INT_PTR) SteamController);
        PrintPointer(L"GetHSteamPipe", (INT_PTR) GetHSteamPipe);
        PrintPointer(L"GetHSteamUser", (INT_PTR) GetHSteamUser);
    }
} static steam_api64;

struct steam_legacy_interfaces {
    INT_PTR SteamApps006;
    INT_PTR SteamUtils006;
    INT_PTR SteamUser017;
    INT_PTR SteamFriends014;

    void PrintPointers() {
        DEBUGOUT(L"Legacy interface pointers:");
        PrintPointer(L"SteamApps006", (INT_PTR) SteamApps006);
        PrintPointer(L"SteamUtils006", (INT_PTR) SteamUtils006);
        PrintPointer(L"SteamUser017", (INT_PTR) SteamUser017);
        PrintPointer(L"SteamFriends014", (INT_PTR) SteamFriends014);
    }
} static legacy_interfaces;

void S_CALLTYPE SteamAPI_InitProxy(const wchar_t* library);

void S_CALLTYPE SteamAPI_CloseProxy();

bool S_CALLTYPE _SteamAPI_Init();

void S_CALLTYPE _SteamAPI_Shutdown();

bool S_CALLTYPE _SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID);

void S_CALLTYPE _SteamAPI_RegisterCallback(INT_PTR pCallback, int iCallback);

void S_CALLTYPE _SteamAPI_UnregisterCallback(INT_PTR pCallback);

void S_CALLTYPE _SteamAPI_RunCallbacks();

HSteamPipe S_CALLTYPE _GetHSteamPipe();

HSteamUser S_CALLTYPE _GetHSteamUser();

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
Latest SDK 1.36:    SteamClient017
*/
ISteamClient017 *SteamClient();

/*
    GTA V Expects:      Ha! It doesn't even expect it. Surprise!
    Latest SDK 1.36:    SteamController003
*/
ISteamController003 *SteamController();
