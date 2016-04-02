#include "stdafx.h"
#include "HookedScript.h"

void ScriptMain() {
    srand(GetTickCount());
    while (true) {
        HookedScript::GetInstance()->Execute();
        WAIT(0);
    }
}

HookedScript *HookedScript::m_Instance = NULL;

void HookedScript::Start(HMODULE hInstance) {
    this->hInstance = hInstance;
    if (Controller::InitSteamController()) {
        DEBUGOUT("Registering ScriptHookV handler...");
        scriptRegister(hInstance, ScriptMain);
    }
    else {
        DEBUGOUT("SteamController init failed.");
    }
}

void HookedScript::Shutdown() {
    DEBUGOUT("Unregistering ScriptHookV handler...");
    scriptUnregister(this->hInstance);
}