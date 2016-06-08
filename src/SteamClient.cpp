#include "stdafx.h"

HSteamPipe hSteamPipe = NULL;
HSteamUser hSteamUser = NULL;
ISteamClient017 *pSteamClient = NULL;
ISteamController003 *pSteamController = NULL;

const std::wstring *GetSteamClientPath() {
    std::wstring *strTempPath = NULL;
    wchar_t wchPath[MAX_PATH];

    HKEY hRegKey;
    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, L"Software\\Valve\\Steam", 0, KEY_QUERY_VALUE, &hRegKey) == ERROR_SUCCESS) {
        DWORD dwLength = sizeof(wchPath) - 1;
        if (RegQueryValueEx(hRegKey, L"InstallPath", NULL, NULL, (LPBYTE) wchPath, &dwLength) == ERROR_SUCCESS) {
            strTempPath = new std::wstring(wchPath);
            strTempPath->append(L"\\");
            strTempPath->append(L"steamclient64.dll");
        }
        RegCloseKey(hRegKey);
    }
    return strTempPath;
}

bool SteamAPI_Init() {
    const std::wstring *pSteamPath = GetSteamClientPath();
    if (!pSteamPath) {
        Logger::Fatal(L"Could not find Steam installer.");
        return false;
    }

    HMODULE hModule = LoadLibrary(pSteamPath->c_str());
    delete pSteamPath;
    if (!hModule) {
        Logger::Fatal(L"Could not load SteamClient library.");
        return false;
    }

    CreateInterfaceFn pFactory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(hModule, "CreateInterface"));
    if (!pFactory) {
        Logger::Fatal(L"Could not get CreateInterface.");
        return false;
    }

    pSteamClient = (ISteamClient017*) pFactory(STEAMCLIENT_INTERFACE_VERSION_017, nullptr);
    if (!pSteamClient) {
        Logger::Fatal(L"Could not get SteamClient interface.");
        return false;
    }

    hSteamPipe = pSteamClient->CreateSteamPipe();
    if (!hSteamPipe) {
        pSteamClient->BShutdownIfAllPipesClosed();
        Logger::Fatal(L"Could not create Steam pipe");
        return false;
    }

    hSteamUser = pSteamClient->ConnectToGlobalUser(hSteamPipe);
    if (!hSteamUser) {
        pSteamClient->BReleaseSteamPipe(hSteamPipe);
        pSteamClient->BShutdownIfAllPipesClosed();
        Logger::Fatal(L"Could not connect to Steam user");
        return false;
    }
    return true;
}

ISteamController003 *SteamController() {
    if (!pSteamController) {
        return pSteamController;
    }
    pSteamController = (ISteamController003 *) pSteamClient->GetISteamController(hSteamUser, hSteamPipe, STEAMCONTROLLER_INTERFACE_VERSION_003);
    return pSteamController;
}