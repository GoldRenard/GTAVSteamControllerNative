#include "stdafx.h"
#include "InjectedScript.h"

InjectedScript *InjectedScript::m_Instance = NULL;

void InjectedScript::Start(HMODULE hInstance) {
    SteamAPI_InitProxy();
}

void InjectedScript::Shutdown() {
    SteamAPI_CloseProxy();
}