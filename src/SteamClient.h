#pragma once

#include "stdafx.h"

typedef void* (*CreateInterfaceFn)(const char *pName, int *pReturnCode);

bool SteamAPI_Init();

ISteamController003 *SteamController();