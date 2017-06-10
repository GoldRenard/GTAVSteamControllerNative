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

void S_CALLTYPE SteamAPI_InitProxy(const wchar_t* library) {
    steam_api64.dll = LoadLibrary(library);
    if (steam_api64.dll == NULL) {
        Logger::Fatal(L"SteamAPI load failed");
    }

    steam_api64.SteamAPI_Init = reinterpret_cast<BOOLPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_Init"));
    steam_api64.SteamAPI_Shutdown = reinterpret_cast<VOIDPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_Shutdown"));
    steam_api64.SteamAPI_RestartAppIfNecessary = reinterpret_cast<RSTPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_RestartAppIfNecessary"));

    steam_api64.SteamAPI_RegisterCallback = reinterpret_cast<REGPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_RegisterCallback"));
    steam_api64.SteamAPI_UnregisterCallback = reinterpret_cast<UNREGPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_UnregisterCallback"));
    steam_api64.SteamAPI_RunCallbacks = reinterpret_cast<VOIDPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_RunCallbacks"));

    steam_api64.SteamInternal_ContextInit = reinterpret_cast<CTXINIT>(GetProcAddress(steam_api64.dll, "SteamInternal_ContextInit"));
    steam_api64.SteamInternal_CreateInterface = reinterpret_cast<CINF>(GetProcAddress(steam_api64.dll, "SteamInternal_CreateInterface"));

    steam_api64.SteamAPI_GetHSteamPipe = reinterpret_cast<HPIPEPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_GetHSteamPipe"));
    steam_api64.SteamAPI_GetHSteamUser = reinterpret_cast<HUSERPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_GetHSteamUser"));

    steam_api64.SteamClient = reinterpret_cast<CLIENTPROC>(GetProcAddress(steam_api64.dll, "SteamClient"));

    steam_api64.PrintPointers();

    _SteamAPI_Init();
}

void S_CALLTYPE SteamAPI_CloseProxy() {
    if (steam_api64.dll != NULL) {
        FreeLibrary(steam_api64.dll);
    }
}

S_API bool S_CALLTYPE _SteamAPI_Init() {
    bool result = steam_api64.SteamAPI_Init();
    if (result) {
        HSteamPipe mPipe = _SteamAPI_GetHSteamPipe();
        HSteamUser mUser = _SteamAPI_GetHSteamUser();
        DEBUGOUT(L"mPipe -> %d", mPipe);
        DEBUGOUT(L"mUser -> %d", mUser);
        steam_api64.SteamController = reinterpret_cast<ISteamController004*>(SteamClient()->GetISteamController(mUser, mPipe, STEAMCONTROLLER_INTERFACE_VERSION_004));
        PrintPointer(L"SteamController", (INT_PTR) SteamController());
        Controller::InitSteamController();
    }
    DEBUGOUT(L"SteamAPI_Init() called -> %d", result);
    return result;
}

S_API void S_CALLTYPE _SteamAPI_Shutdown() {
    steam_api64.SteamAPI_Shutdown();
    DEBUGOUT(L"SteamAPI_Shutdown() called");
}

S_API bool S_CALLTYPE _SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID) {
    bool result = steam_api64.SteamAPI_RestartAppIfNecessary(unOwnAppID);
    DEBUGOUT(L"SteamAPI_RestartAppIfNecessary(%d) called -> %d", unOwnAppID, result);
    return result;
}

S_API void S_CALLTYPE _SteamAPI_RegisterCallback(INT_PTR pCallback, int iCallback) {
    steam_api64.SteamAPI_RegisterCallback(pCallback, iCallback);
    DEBUGOUT(L"SteamAPI_RegisterCallback(0x%I64X, %d) called", pCallback, iCallback);
}

S_API void S_CALLTYPE _SteamAPI_UnregisterCallback(INT_PTR pCallback) {
    steam_api64.SteamAPI_UnregisterCallback(pCallback);
    DEBUGOUT(L"SteamAPI_UnregisterCallback(0x%I64X) called", pCallback);
}

S_API void S_CALLTYPE _SteamAPI_RunCallbacks() {
    if (m_BaseScript != NULL && g_CompatibleVersion) {
        m_BaseScript->Execute();
    }
    steam_api64.SteamAPI_RunCallbacks();
}

S_API void * S_CALLTYPE _SteamInternal_ContextInit(void *pContextInitData) {
    void * result = steam_api64.SteamInternal_ContextInit(pContextInitData);
    DEBUGOUT(L"SteamInternal_ContextInit(0x%I64X) called -> 0x%I64X", pContextInitData, result);
    return result;
}

S_API void * S_CALLTYPE _SteamInternal_CreateInterface(const char *ver) {
    void * result = steam_api64.SteamInternal_CreateInterface(ver);
    DEBUGOUT(L"SteamInternal_CreateInterface('%s') called -> 0x%I64X", ver, result);
    return result;
}

S_API HSteamPipe S_CALLTYPE _SteamAPI_GetHSteamPipe() {
    HSteamPipe result = steam_api64.SteamAPI_GetHSteamPipe();
    DEBUGOUT(L"SteamAPI_GetHSteamPipe() requested -> [0x%I64X]", result);
    return result;
}

S_API HSteamUser S_CALLTYPE _SteamAPI_GetHSteamUser() {
    HSteamUser result = steam_api64.SteamAPI_GetHSteamUser();
    DEBUGOUT(L"SteamAPI_GetHSteamUser() requested -> [0x%I64X]", result);
    return result;
}

ISteamClient017 *SteamClient() {
    return steam_api64.SteamClient();
}

ISteamController004 *SteamController() {
    return steam_api64.SteamController;
}