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

BOOL VersionUtils::IsValidEnvironment() {
    TCHAR currentVersion[64];
    memset(&currentVersion[0], 0, sizeof(currentVersion));
    EVersionCheckResult mResult = VersionUtils::IsValidModuleVersion(GAME_MODULE_NAME, REQUIRED_GAME_VERSION, currentVersion);
    switch (mResult) {
        case INVALID:
            Logger::Fatal("Unsupported game version %s, %s is required. Download new version of plugin.", currentVersion, REQUIRED_GAME_VERSION);
            return FALSE;
        case NOT_FOUND:
            DEBUGOUT("Executing out of %s context", GAME_MODULE_NAME);
            return FALSE;
        default:
            break;
    }
    return TRUE;
}

EVersionCheckResult VersionUtils::IsValidModuleVersion(const char* mName, const char* mRequiredVersion, char* mCurrentVersion) {
    HANDLE hProcess = GetCurrentProcess();
    HMODULE hMods[1024];
    DWORD cbNeeded;
    HMODULE hModule = NULL;

    if (EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded)) {
        for (unsigned int i = 0; i < (cbNeeded / sizeof(HMODULE)); i++) {
            TCHAR szModName[MAX_PATH];
            if (GetModuleFileNameEx(hProcess, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR))) {
                std::string szModuleName = szModName;
                size_t pos = szModuleName.find(mName);
                if (std::string::npos != pos) {
                    hModule = hMods[i];
                    DEBUGOUT("Found loaded %s module as %s (0x%08X).", mName, szModName, hMods[i]);
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

BOOL VersionUtils::GetFileVersion(const char *fileName, char *ver) {
    DWORD dwHandle, sz = GetFileVersionInfoSizeA(fileName, &dwHandle);
    if (0 == sz) {
        DEBUGOUT("VersionUtils::GetFileVersion() [GetFileVersionInfoSizeA] call failed for \"%s\"", fileName);
        return FALSE;
    }
    char *buf = new char[sz];
    if (!GetFileVersionInfoA(fileName, dwHandle, sz, &buf[0])) {
        DEBUGOUT("VersionUtils::GetFileVersion() [GetFileVersionInfoA] call failed for \"%s\"", fileName);
        delete buf;
        return FALSE;
    }
    VS_FIXEDFILEINFO * pvi;
    sz = sizeof(VS_FIXEDFILEINFO);
    if (!VerQueryValueA(&buf[0], "\\", (LPVOID*) &pvi, (unsigned int*) &sz)) {
        DEBUGOUT("VersionUtils::GetFileVersion() [VerQueryValueA] call failed for \"%s\"", fileName);
        delete buf;
        return FALSE;
    }
    sprintf(ver, "%d.%d.%d.%d",
        pvi->dwProductVersionMS >> 16,
        pvi->dwFileVersionMS & 0xFFFF,
        pvi->dwFileVersionLS >> 16,
        pvi->dwFileVersionLS & 0xFFFF
        );
    DEBUGOUT("VersionUtils::GetFileVersion() returns \"%s\" for \"%s\"", ver, fileName);
    delete buf;
    return TRUE;
}

BOOL VersionUtils::HasFileVersion(const char *fileName, const char *expectedVersion, char *currentVersion) {
    if (!GetFileVersion(fileName, currentVersion)) {
        sprintf(currentVersion, "?.?.?.?");
        DEBUGOUT("Cannot get version for file: %s", fileName);
        return FALSE;
    }
    return strcmp(currentVersion, expectedVersion) == 0;
}