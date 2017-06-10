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
#define S_API extern "C"

typedef void        (S_CALLTYPE *VOIDPROC)();
typedef bool        (S_CALLTYPE *BOOLPROC)();
typedef bool        (S_CALLTYPE *RSTPROC)(uint32 unOwnAppID);
typedef void        (S_CALLTYPE *REGPROC)(INT_PTR pCallback, int iCallback);
typedef void        (S_CALLTYPE *UNREGPROC)(INT_PTR pCallback);

typedef void *      (S_CALLTYPE *CTXINIT)(void *pContextInitData);
typedef void *      (S_CALLTYPE *CINF)(const char *ver);

typedef INT_PTR(S_CALLTYPE *APIPROC)();
typedef HSteamUser(S_CALLTYPE *HUSERPROC)();
typedef HSteamPipe(S_CALLTYPE *HPIPEPROC)();

typedef ISteamController004*    (S_CALLTYPE *CONTROLLERPROC)();
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

    CTXINIT SteamInternal_ContextInit;
    CINF SteamInternal_CreateInterface;

    CLIENTPROC SteamClient;
    ISteamController004* SteamController;

    HPIPEPROC SteamAPI_GetHSteamPipe;
    HUSERPROC SteamAPI_GetHSteamUser;

    void PrintPointers() {
        DEBUGOUT(L"Proxy function pointers:");
        PrintPointer(L"SteamAPI_Init", (INT_PTR) SteamAPI_Init);
        PrintPointer(L"SteamAPI_Shutdown", (INT_PTR) SteamAPI_Shutdown);
        PrintPointer(L"SteamAPI_RestartAppIfNecessary", (INT_PTR) SteamAPI_RestartAppIfNecessary);

        PrintPointer(L"SteamAPI_RegisterCallback", (INT_PTR) SteamAPI_RegisterCallback);
        PrintPointer(L"SteamAPI_UnregisterCallback", (INT_PTR) SteamAPI_UnregisterCallback);
        PrintPointer(L"SteamAPI_RunCallbacks", (INT_PTR) SteamAPI_RunCallbacks);

        PrintPointer(L"SteamInternal_ContextInit", (INT_PTR) SteamInternal_ContextInit);
        PrintPointer(L"SteamInternal_CreateInterface", (INT_PTR) SteamInternal_CreateInterface);

        PrintPointer(L"SteamAPI_GetHSteamPipe", (INT_PTR) SteamAPI_GetHSteamPipe);
        PrintPointer(L"SteamAPI_GetHSteamUser", (INT_PTR) SteamAPI_GetHSteamUser);

        PrintPointer(L"SteamAPI_GetHSteamUser", (INT_PTR) SteamAPI_GetHSteamUser);
        PrintPointer(L"SteamController", (INT_PTR) SteamController);
    }
} static steam_api64;

void S_CALLTYPE SteamAPI_InitProxy(const wchar_t* library);

void S_CALLTYPE SteamAPI_CloseProxy();

S_API bool S_CALLTYPE _SteamAPI_Init();

S_API void S_CALLTYPE _SteamAPI_Shutdown();

S_API bool S_CALLTYPE _SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID);

S_API void S_CALLTYPE _SteamAPI_RegisterCallback(INT_PTR pCallback, int iCallback);

S_API void S_CALLTYPE _SteamAPI_UnregisterCallback(INT_PTR pCallback);

S_API void S_CALLTYPE _SteamAPI_RunCallbacks();

S_API void * S_CALLTYPE _SteamInternal_ContextInit(void *pContextInitData);

S_API void * S_CALLTYPE _SteamInternal_CreateInterface(const char *ver);

S_API HSteamPipe S_CALLTYPE _SteamAPI_GetHSteamPipe();

S_API HSteamUser S_CALLTYPE _SteamAPI_GetHSteamUser();

/*
GTA V Expects:      Ha! It doesn't even expect it. Surprise!
Latest SDK 1.38a:    SteamClient017
*/
ISteamClient017 *SteamClient();

/*
    GTA V Expects:      Ha! It doesn't even expect it. Surprise!
    Latest SDK 1.38a:    SteamController004
*/
ISteamController004 *SteamController();
