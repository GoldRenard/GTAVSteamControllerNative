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
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

#include "log.h"
#include "controller.h"

#ifdef SCRIPT_ASI
#include "inc\natives.h"
#include "inc\types.h"
#include "inc\enums.h"
#include "inc\main.h"
#else
#include <string>
#include <vector>
#include <sstream>
#include <Psapi.h>
#include <timeapi.h>

#pragma comment(lib, "winmm.lib")

extern MODULEINFO g_MainModuleInfo;

#include "Pattern.h"
#include "Types.h"
#include "pgCollection.h"
#include "scrThread.h"
#include "natives.h"
#include "RAGEHelper.h"

void Tick();
void Run();
void RunUnreliable();

#endif

// TODO: reference additional headers your program requires here
