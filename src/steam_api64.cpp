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

    steam_api64.SteamApps = reinterpret_cast<APIPROC>(GetProcAddress(steam_api64.dll, "SteamApps"));
    steam_api64.SteamFriends = reinterpret_cast<APIPROC>(GetProcAddress(steam_api64.dll, "SteamFriends"));
    steam_api64.SteamUser = reinterpret_cast<APIPROC>(GetProcAddress(steam_api64.dll, "SteamUser"));
    steam_api64.SteamUserStats = reinterpret_cast<APIPROC>(GetProcAddress(steam_api64.dll, "SteamUserStats"));
    steam_api64.SteamUtils = reinterpret_cast<APIPROC>(GetProcAddress(steam_api64.dll, "SteamUtils"));
    steam_api64.SteamClient = reinterpret_cast<CLIENTPROC>(GetProcAddress(steam_api64.dll, "SteamClient"));
    steam_api64.SteamController = reinterpret_cast<CONTROLLERPROC>(GetProcAddress(steam_api64.dll, "SteamController"));
    steam_api64.GetHSteamPipe = reinterpret_cast<HPIPEPROC>(GetProcAddress(steam_api64.dll, "GetHSteamPipe"));
    steam_api64.GetHSteamUser = reinterpret_cast<HUSERPROC>(GetProcAddress(steam_api64.dll, "GetHSteamUser"));
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
        HSteamPipe mPipe = _GetHSteamPipe();
        HSteamUser mUser = _GetHSteamUser();

        legacy_interfaces.SteamApps006 = SteamClient()->GetISteamApps(mUser, mPipe, STEAMAPPS_INTERFACE_VERSION_006);
        legacy_interfaces.SteamFriends014 = SteamClient()->GetISteamFriends(mUser, mPipe, STEAMFRIENDS_INTERFACE_VERSION_014);
        legacy_interfaces.SteamUser017 = SteamClient()->GetISteamUser(mUser, mPipe, STEAMUSER_INTERFACE_VERSION_017);
        legacy_interfaces.SteamUtils006 = SteamClient()->GetISteamUtils(mUser, STEAMUTILS_INTERFACE_VERSION_006);
        legacy_interfaces.PrintPointers();

        Controller::InitSteamController();
    }
    DEBUGOUT(L"SteamAPI_Init() called -> %d", result);
    return result;
}

void S_CALLTYPE _SteamAPI_Shutdown() {
    steam_api64.SteamAPI_Shutdown();
    DEBUGOUT(L"SteamAPI_Shutdown() called");
}

bool S_CALLTYPE _SteamAPI_RestartAppIfNecessary(uint32 unOwnAppID) {
    bool result = steam_api64.SteamAPI_RestartAppIfNecessary(unOwnAppID);
    DEBUGOUT(L"SteamAPI_RestartAppIfNecessary(%d) called -> %d", unOwnAppID, result);
    return result;
}

void S_CALLTYPE _SteamAPI_RegisterCallback(INT_PTR pCallback, int iCallback) {
    steam_api64.SteamAPI_RegisterCallback(pCallback, iCallback);
    DEBUGOUT(L"SteamAPI_RegisterCallback(0x%I64X, %d) called", pCallback, iCallback);
}

void S_CALLTYPE _SteamAPI_UnregisterCallback(INT_PTR pCallback) {
    steam_api64.SteamAPI_UnregisterCallback(pCallback);
    DEBUGOUT(L"SteamAPI_UnregisterCallback(0x%I64X) called", pCallback);
}

void S_CALLTYPE _SteamAPI_RunCallbacks() {
    if (m_BaseScript != NULL && g_CompatibleVersion) {
        m_BaseScript->Execute();
    }
    steam_api64.SteamAPI_RunCallbacks();
}

INT_PTR S_CALLTYPE _SteamApps() {
    DEBUGOUT(L"SteamApps() requested -> [0x%I64X]", legacy_interfaces.SteamApps006);
    return legacy_interfaces.SteamApps006;
}

INT_PTR S_CALLTYPE _SteamUserStats() {
    INT_PTR result = steam_api64.SteamUserStats();
    DEBUGOUT(L"SteamUserStats() requested -> [0x%I64X]", result);
    return result;
}

INT_PTR S_CALLTYPE _SteamUtils() {
    DEBUGOUT(L"SteamUtils() requested -> [0x%I64X]", legacy_interfaces.SteamUtils006);
    return legacy_interfaces.SteamUtils006;
}

INT_PTR S_CALLTYPE _SteamUser() {
    DEBUGOUT(L"SteamUser() requested -> [0x%I64X]", legacy_interfaces.SteamUser017);
    return legacy_interfaces.SteamUser017;
}

INT_PTR S_CALLTYPE _SteamFriends() {
    DEBUGOUT(L"SteamFriends() requested -> [0x%I64X]", legacy_interfaces.SteamFriends014);
    return legacy_interfaces.SteamFriends014;
}

HSteamPipe S_CALLTYPE _GetHSteamPipe() {
    HSteamPipe result = steam_api64.GetHSteamPipe();
    DEBUGOUT(L"GetHSteamPipe() requested -> [0x%I64X]", result);
    return result;
}

HSteamUser S_CALLTYPE _GetHSteamUser() {
    HSteamUser result = steam_api64.GetHSteamUser();
    DEBUGOUT(L"GetHSteamUser() requested -> [0x%I64X]", result);
    return result;
}

ISteamClient017 *SteamClient() {
    return steam_api64.SteamClient();
}

ISteamController003 *SteamController() {
    return steam_api64.SteamController();
}