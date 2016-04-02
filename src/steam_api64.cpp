#include "stdafx.h"

void S_CALLTYPE SteamAPI_InitProxy() {
    // TODO It is better to extract it from resource to temp
    steam_api64.dll = LoadLibrary("steam_api64_.dll");
    if (steam_api64.dll == NULL) {
        Logger::Fatal("SteamAPI load failed");
    }

    steam_api64.SteamAPI_Init = reinterpret_cast<BOOLPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_Init"));
    steam_api64.SteamAPI_Shutdown = reinterpret_cast<VOIDPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_Shutdown"));
    steam_api64.SteamAPI_RestartAppIfNecessary = reinterpret_cast<RSTPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_RestartAppIfNecessary"));

    steam_api64.SteamAPI_RegisterCallback = reinterpret_cast<REGPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_RegisterCallback"));
    steam_api64.SteamAPI_UnregisterCallback = reinterpret_cast<UNREGPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_UnregisterCallback"));
    steam_api64.SteamAPI_RunCallbacks = reinterpret_cast<VOIDPROC>(GetProcAddress(steam_api64.dll, "SteamAPI_RunCallbacks"));

    // TODO return explicit interface versions of SDK 1.27. See header for more info.
    steam_api64.SteamApps = reinterpret_cast<APIPROC>(GetProcAddress(steam_api64.dll, "SteamApps"));
    steam_api64.SteamFriends = reinterpret_cast<APIPROC>(GetProcAddress(steam_api64.dll, "SteamFriends"));
    steam_api64.SteamUser = reinterpret_cast<APIPROC>(GetProcAddress(steam_api64.dll, "SteamUser"));
    steam_api64.SteamUserStats = reinterpret_cast<APIPROC>(GetProcAddress(steam_api64.dll, "SteamUserStats"));
    steam_api64.SteamUtils = reinterpret_cast<APIPROC>(GetProcAddress(steam_api64.dll, "SteamUtils"));
    steam_api64.SteamController = reinterpret_cast<CONTROLLERPROC>(GetProcAddress(steam_api64.dll, "SteamController"));
    steam_api64.PrintPointers();

    _SteamAPI_Init();
}

void S_CALLTYPE SteamAPI_CloseProxy() {
    if (steam_api64.dll != NULL) {
        FreeLibrary(steam_api64.dll);
    }
}

bool S_CALLTYPE _SteamAPI_Init() {
    bool result = steam_api64.SteamAPI_Init();
    if (result) {
        Controller::InitSteamController();
    }
    DEBUGOUT("SteamAPI_Init() called -> %d", result);
    return result;
}

void S_CALLTYPE _SteamAPI_Shutdown() {
    steam_api64.SteamAPI_Shutdown();
    DEBUGOUT("SteamAPI_Shutdown() called");
}

bool S_CALLTYPE _SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID) {
    bool result = steam_api64.SteamAPI_RestartAppIfNecessary(unOwnAppID);
    DEBUGOUT("SteamAPI_RestartAppIfNecessary(%d) called -> %d", unOwnAppID, result);
    return result;
}

void S_CALLTYPE _SteamAPI_RegisterCallback(INT_PTR pCallback, int iCallback) {
    steam_api64.SteamAPI_RegisterCallback(pCallback, iCallback);
    DEBUGOUT("SteamAPI_RegisterCallback(0x%I64X, %d) called", pCallback, iCallback);
}

void S_CALLTYPE _SteamAPI_UnregisterCallback(INT_PTR pCallback) {
    steam_api64.SteamAPI_UnregisterCallback(pCallback);
    DEBUGOUT("SteamAPI_UnregisterCallback(0x%I64X) called", pCallback);
}

void S_CALLTYPE _SteamAPI_RunCallbacks() {
    if (m_BaseScript != NULL && g_CompatibleVersion) {
        m_BaseScript->Execute();
    }
    steam_api64.SteamAPI_RunCallbacks();
}

INT_PTR S_CALLTYPE _SteamApps() {
    INT_PTR result = steam_api64.SteamApps();
    DEBUGOUT("SteamApps() requested -> [0x%I64X]", result);
    return steam_api64.SteamApps();
}

INT_PTR S_CALLTYPE _SteamUserStats() {
    INT_PTR result = steam_api64.SteamUserStats();
    DEBUGOUT("SteamUserStats() requested -> [0x%I64X]", result);
    return result;
}

INT_PTR S_CALLTYPE _SteamUtils() {
    INT_PTR result = steam_api64.SteamUtils();
    DEBUGOUT("SteamUtils() requested -> [0x%I64X]", result);
    return result;
}

INT_PTR S_CALLTYPE _SteamUser() {
    INT_PTR result = steam_api64.SteamUser();
    DEBUGOUT("SteamUser() requested -> [0x%I64X]", result);
    return result;
}

INT_PTR S_CALLTYPE _SteamFriends() {
    INT_PTR result = steam_api64.SteamFriends();
    DEBUGOUT("SteamFriends() requested -> [0x%I64X]", result);
    return result;
}

ISteamController003 *SteamController() {
    return steam_api64.SteamController();
}