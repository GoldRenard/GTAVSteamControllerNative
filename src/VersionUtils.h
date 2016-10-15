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

#define GAME_MODULE_NAME            L"GTA5.exe"
#define REQUIRED_GAME_VERSION       L"1.0.877.1"

enum EVersionCheckResult {
    VALID = 0,
    INVALID = 1,
    NOT_FOUND
};

class VersionUtils {
public:

    // Checks versions of game itself
    static BOOL IsValidEnvironment();

    // Returns version of file
    static BOOL GetFileVersion(const WCHAR* fileName, WCHAR* ver);

    // Checks version of file
    static BOOL HasFileVersion(const WCHAR* fileName, const WCHAR* expectedVersion, WCHAR* currentVersion);

    // Checks version of module loaded by current process
    static EVersionCheckResult IsValidModuleVersion(const WCHAR* mName, const WCHAR* mRequiredVersion, WCHAR* mCurrentVersion);
};
