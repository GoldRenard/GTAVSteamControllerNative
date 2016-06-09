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

#define VERSION_SIZE 64

BOOL VersionUtils::IsValidEnvironment() {
    WCHAR currentVersion[VERSION_SIZE];
    memset(&currentVersion[0], 0, sizeof(currentVersion));
    EVersionCheckResult mResult = VersionUtils::IsValidModuleVersion(GAME_MODULE_NAME, REQUIRED_GAME_VERSION, currentVersion);
    switch (mResult) {
        case INVALID:
            Logger::Fatal(L"Unsupported game version %s, %s is required. Download new version of plugin.", currentVersion, REQUIRED_GAME_VERSION);
            return FALSE;
        case NOT_FOUND:
            DEBUGOUT(L"Executing out of %s context", GAME_MODULE_NAME);
            return FALSE;
        default:
            break;
    }
    return TRUE;
}

EVersionCheckResult VersionUtils::IsValidModuleVersion(const WCHAR* mName, const WCHAR* mRequiredVersion, WCHAR* mCurrentVersion) {
    HANDLE hProcess = GetCurrentProcess();
    HMODULE hMods[1024];
    DWORD cbNeeded;
    HMODULE hModule = NULL;

    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
        for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
            WCHAR szModName[MAX_PATH];
            if (GetModuleFileNameEx(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(WCHAR))) {
                std::wstring szModuleName = szModName;
                size_t pos = szModuleName.find(mName);
                if (std::string::npos != pos) {
                    hModule = hMods[i];
                    DEBUGOUT(L"Found loaded %s module as %s (0x%08X).", mName, szModName, hMods[i]);
                    if (!VersionUtils::HasFileVersion(szModName, mRequiredVersion, mCurrentVersion)) {
                        return EVersionCheckResult::INVALID;
                    }
                    break;
                }
            }
        }
    }
    return !hModule ? EVersionCheckResult::NOT_FOUND : EVersionCheckResult::VALID;
}

BOOL VersionUtils::GetFileVersion(const WCHAR *fileName, WCHAR *ver) {
    DWORD dwHandle, sz = GetFileVersionInfoSize(fileName, &dwHandle);
    if (0 == sz) {
        DEBUGOUT(L"VersionUtils::GetFileVersion() [GetFileVersionInfoSizeA] call failed for \"%s\"", fileName);
        return FALSE;
    }
    char *buf = new char[sz];
    if (!GetFileVersionInfo(fileName, dwHandle, sz, &buf[0])) {
        DEBUGOUT(L"VersionUtils::GetFileVersion() [GetFileVersionInfoA] call failed for \"%s\"", fileName);
        delete buf;
        return FALSE;
    }
    VS_FIXEDFILEINFO * pvi;
    sz = sizeof(VS_FIXEDFILEINFO);
    if (!VerQueryValueA(&buf[0], "\\", (LPVOID*) &pvi, (unsigned int*) &sz)) {
        DEBUGOUT(L"VersionUtils::GetFileVersion() [VerQueryValueA] call failed for \"%s\"", fileName);
        delete buf;
        return FALSE;
    }
    swprintf(ver, VERSION_SIZE + 1, L"%d.%d.%d.%d",
        pvi->dwProductVersionMS >> 16,
        pvi->dwFileVersionMS & 0xFFFF,
        pvi->dwFileVersionLS >> 16,
        pvi->dwFileVersionLS & 0xFFFF
    );
    DEBUGOUT(L"VersionUtils::GetFileVersion() returns \"%s\" for \"%s\"", ver, fileName);
    delete buf;
    return TRUE;
}

BOOL VersionUtils::HasFileVersion(const WCHAR *fileName, const WCHAR *expectedVersion, WCHAR *currentVersion) {
    if (!GetFileVersion(fileName, currentVersion)) {
        swprintf(currentVersion, VERSION_SIZE + 1, L"?.?.?.?");
        DEBUGOUT(L"Cannot get version for file: %s", fileName);
        return FALSE;
    }
    return wcscmp(currentVersion, expectedVersion) == 0;
}