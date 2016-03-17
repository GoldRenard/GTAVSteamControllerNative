#include "stdafx.h"
#include "script.h"

BOOL APIENTRY DllMain(HMODULE hInstance, DWORD reason, LPVOID lpReserved) {
	switch (reason) {
		case DLL_PROCESS_ATTACH:
			Log::Init(hInstance);
			DEBUGOUT("Steam Controller Native initialized.");
			scriptRegister(hInstance, ScriptMain);
			break;
		case DLL_PROCESS_DETACH:
			scriptUnregister(hInstance);
			break;
	}
	return TRUE;
}