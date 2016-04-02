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
        DEBUGOUT(L"Registering ScriptHookV handler...");
        scriptRegister(hInstance, ScriptMain);
    }
    else {
        DEBUGOUT(L"SteamController init failed.");
    }
}

void HookedScript::Shutdown() {
    DEBUGOUT(L"Unregistering ScriptHookV handler...");
    scriptUnregister(this->hInstance);
}