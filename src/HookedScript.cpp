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
    DEBUGOUT("Registering ScriptHookV handler...");
    scriptRegister(hInstance, ScriptMain);
}

void HookedScript::Shutdown() {
    DEBUGOUT("Unregistering ScriptHookV handler...");
    scriptUnregister(this->hInstance);
}