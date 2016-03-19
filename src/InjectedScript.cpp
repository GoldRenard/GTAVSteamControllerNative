#include "stdafx.h"
#include "InjectedScript.h"

InjectedScript *InjectedScript::m_Instance = NULL;

BlipList* pBlipList;
ScriptThread_VTable pThreadOriginal;
ScriptThread_VTable pThreadModified;

HANDLE mainFiber;
DWORD wakeAt;

void WAIT(DWORD ms) {
    wakeAt = timeGetTime() + ms;
    SwitchToFiber(mainFiber);
}

void __stdcall ReliableScriptFunction(LPVOID lpParameter) {
    try {
        while (1) {
            InjectedScript::GetInstance()->Execute();
            WAIT(0);
        }
    }
    catch (...) {
        Logger::Fatal("Failed scriptFiber");
    }
}

void Tick() {
    if (mainFiber == nullptr)
        mainFiber = ConvertThreadToFiber(nullptr);

    static HANDLE reliableFiber;
    if (reliableFiber)
        SwitchToFiber(reliableFiber);
    else
        reliableFiber = CreateFiber(NULL, ReliableScriptFunction, nullptr);
}

eThreadState Trampoline(ScriptThread* This) {
    scrThread* runningThread = GetActiveThread();
    SetActiveThread(This);
    Tick();
    SetActiveThread(runningThread);
    return pThreadOriginal.Run(This);
}

bool AttemptScriptHook() {
    pgPtrCollection<ScriptThread>* threads = GetThreadCollection(pBlipList);

    if (!threads) {
        return false;
    }

    for (UINT16 i = 0; i < threads->count(); i++) {
        ScriptThread* pThread = threads->at(i);

        if (!pThread)
            continue;

        //s0biet originally had some junk thread that was called for like 2 seconds then died. This thread is better.
        if (pThread->GetContext()->ScriptHash != MAIN_PERSISTENT) {
            continue;
        }

        // Now what? We need to find a target thread and hook its "Tick" function
        if (pThreadOriginal.Deconstructor == NULL) {
            memcpy(&pThreadOriginal, (DWORD64*) ((DWORD64*) pThread)[0], sizeof(pThreadOriginal)); //Create a backup of the original table so we can call the original functions from our hook.
            memcpy(&pThreadModified, &pThreadOriginal, sizeof(ScriptThread_VTable)); //Construct our VMT replacement table.

            pThreadModified.Run = Trampoline; //Replace the .Run method in the new table with our method.
        }

        if (((DWORD64*) pThread)[0] != (DWORD64) &pThreadModified) { //If the table is not VMT Hooked.
            DEBUGOUT("Hooking thread [%i] (0x%X)", pThread->GetContext()->ThreadId, pThread->GetContext()->ScriptHash);
            ((DWORD64*) pThread)[0] = (DWORD64) &pThreadModified; //Replace the VMT pointer with a pointer to our new VMT.
            DEBUGOUT("Hooked thread [%i] (0x%X)", pThread->GetContext()->ThreadId, pThread->GetContext()->ScriptHash);
            return true;
        }
    }
    return false;
}

DWORD WINAPI lpHookScript(LPVOID lpParam) {
    while (!AttemptScriptHook()) {
        Sleep(100);
    }
    return 0;
}

void InjectedScript::Start(HMODULE hInstance) {
    CreateThread(0, 0, lpHookScript, 0, 0, 0);
}

void InjectedScript::Shutdown() {}