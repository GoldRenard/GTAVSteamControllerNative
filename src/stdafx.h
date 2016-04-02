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

// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>
#include <string>
#include <Psapi.h>

#include "Logger.h"

#ifdef SCRIPT_ASI
#include "steam/steam_api.h"
#include "inc\natives.h"
#include "inc\types.h"
#include "inc\enums.h"
#include "inc\main.h"
#else
#include <vector>
#include <sstream>
#include <timeapi.h>

#include "steam_types.h"
#include "ISteamClient017.h"
#include "ISteamController003.h"
#include "steam_api64.h"
#include "Pattern.h"
#include "NativeInvoker.h"
#include "natives.h"

extern MODULEINFO g_MainModuleInfo;

extern BOOL g_CompatibleVersion;

#endif

#include "Controller.h"
#include "VersionUtils.h"
#include "BaseScript.h"

extern BaseScript *m_BaseScript;
