#include "stdafx.h"
#include "HookedScript.h"

void ScriptMain() {
    DEBUGOUT(L"Initializing SteamAPI...");
    if (!SteamAPI_Init()) {
        Logger::Fatal(L"Failed to initialize Steam API. Controller support will not work.");
        return;
    }

    if (!Controller::InitSteamController()) {
        Logger::Warn(L"Failed to initialize Steam Controller.");
        return;
    }

    DEBUGOUT(L"SteamController API initialized, entering main loop.");
    srand(GetTickCount());
    while (true) {
        HookedScript::GetInstance()->Execute();
        WAIT(0);
    }
}

HookedScript *HookedScript::m_Instance = NULL;

void HookedScript::Start(HMODULE hInstance) {
    this->hInstance = hInstance;
    scriptRegister(hInstance, ScriptMain);
}

void HookedScript::Shutdown() {
    DEBUGOUT(L"Unregistering ScriptHookV handler...");
    scriptUnregister(this->hInstance);
}