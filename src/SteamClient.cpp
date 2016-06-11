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

HSteamPipe hSteamPipe = NULL;
HSteamUser hSteamUser = NULL;
ISteamClient017 *pSteamClient = NULL;
ISteamController003 *pSteamController = NULL;

bool SteamAPI_Init() {
    HMODULE hModule = GetModuleHandle(L"steamclient64.dll");
    if (!hModule) {
        Logger::Fatal(L"Failed to get SteamClient library.");
        return false;
    }

    CreateInterfaceFn pFactory = reinterpret_cast<CreateInterfaceFn>(GetProcAddress(hModule, "CreateInterface"));
    DEBUGOUT(L"CreateInterfaceFn->0x%I64X", pFactory);
    if (!pFactory) {
        Logger::Fatal(L"Failed to get CreateInterface factory.");
        return false;
    }

    pSteamClient = (ISteamClient017*) pFactory(STEAMCLIENT_INTERFACE_VERSION_017, nullptr);
    DEBUGOUT(L"pSteamClient->0x%I64X", pSteamClient);
    if (!pSteamClient) {
        Logger::Fatal(L"Failed to get SteamClient interface.");
        return false;
    }

    hSteamPipe = pSteamClient->CreateSteamPipe();
    DEBUGOUT(L"Steam pipe: %d", hSteamPipe);
    if (!hSteamPipe) {
        pSteamClient->BShutdownIfAllPipesClosed();
        Logger::Fatal(L"Failed to create a Steam pipe");
        return false;
    }

    hSteamUser = pSteamClient->ConnectToGlobalUser(hSteamPipe);
    DEBUGOUT(L"Steam user: %d", hSteamUser);
    if (!hSteamUser) {
        pSteamClient->BReleaseSteamPipe(hSteamPipe);
        pSteamClient->BShutdownIfAllPipesClosed();
        Logger::Fatal(L"Failed to connect to global Steam user");
        return false;
    }
    return true;
}

ISteamController003 *SteamController() {
    if (!pSteamController) {
        pSteamController = (ISteamController003 *) pSteamClient->GetISteamController(hSteamUser, hSteamPipe, STEAMCONTROLLER_INTERFACE_VERSION_003);
        DEBUGOUT(L"pSteamController->0x%I64X", pSteamClient);
    }
    return pSteamController;
}