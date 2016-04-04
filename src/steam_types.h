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

#define abstract_class class __declspec( novtable )

#define STEAMAPPS_INTERFACE_VERSION_006     "STEAMAPPS_INTERFACE_VERSION006"
#define STEAMUTILS_INTERFACE_VERSION_006    "SteamUtils006"
#define STEAMUSER_INTERFACE_VERSION_017     "SteamUser017"
#define STEAMFRIENDS_INTERFACE_VERSION_014  "SteamFriends014"

typedef unsigned long long uint64;
typedef unsigned __int32 uint32;
typedef unsigned short uint16;

typedef int int32;

// handle to a communication pipe to the Steam client
typedef int32 HSteamPipe;
// handle to single instance of a steam user
typedef int32 HSteamUser;
typedef uint64 SteamAPICall_t;

typedef void(*SteamAPIWarningMessageHook_t)(int hpipe, const char *message);

enum EAccountType {
    k_EAccountTypeInvalid = 0,
    k_EAccountTypeIndividual = 1,		// single user account
    k_EAccountTypeMultiseat = 2,		// multiseat (e.g. cybercafe) account
    k_EAccountTypeGameServer = 3,		// game server account
    k_EAccountTypeAnonGameServer = 4,	// anonymous game server account
    k_EAccountTypePending = 5,			// pending
    k_EAccountTypeContentServer = 6,	// content server
    k_EAccountTypeClan = 7,
    k_EAccountTypeChat = 8,
    k_EAccountTypeConsoleUser = 9,		// Fake SteamID for local PSN account on PS3 or Live account on 360, etc.
    k_EAccountTypeAnonUser = 10,

    // Max of 16 items in this field
    k_EAccountTypeMax
};
