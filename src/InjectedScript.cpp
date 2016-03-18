#include "stdafx.h"
#include "InjectedScript.h"

InjectedScript *InjectedScript::m_Instance = NULL;

BlipList* pBlipList;
GtaThread_VTable gGtaThreadOriginal;
GtaThread_VTable gGtaThreadNew;

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
        Log::Fatal("Failed scriptFiber");
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

eThreadState Trampoline(GtaThread* This) {
    rage::scrThread* runningThread = GetActiveThread();
    SetActiveThread(This);
    Tick();
    SetActiveThread(runningThread);
    return gGtaThreadOriginal.Run(This);
}

bool AttemptScriptHook() {
    rage::pgPtrCollection<GtaThread>* threadCollection = GetGtaThreadCollection(pBlipList);

    if (!threadCollection) {
        return false;
    }

    for (UINT16 i = 0; i < threadCollection->count(); i++) {
        GtaThread* pThread = threadCollection->at(i);

        if (!pThread)
            continue;

        //s0biet originally had some junk thread that was called for like 2 seconds then died. This thread is better.
        if (pThread->GetContext()->ScriptHash != MAIN_PERSISTENT) {
            continue;
        }

        // Now what? We need to find a target thread and hook its "Tick" function
        if (gGtaThreadOriginal.Deconstructor == NULL) {
            memcpy(&gGtaThreadOriginal, (DWORD64*) ((DWORD64*) pThread)[0], sizeof(gGtaThreadOriginal)); //Create a backup of the original table so we can call the original functions from our hook.
            memcpy(&gGtaThreadNew, &gGtaThreadOriginal, sizeof(GtaThread_VTable)); //Construct our VMT replacement table.

            gGtaThreadNew.Run = Trampoline; //Replace the .Run method in the new table with our method.
        }

        if (((DWORD64*) pThread)[0] != (DWORD64) &gGtaThreadNew) { //If the table is not VMT Hooked.
            DEBUGOUT("Hooking thread [%i] (0x%X)", pThread->GetContext()->ThreadId, pThread->GetContext()->ScriptHash);
            ((DWORD64*) pThread)[0] = (DWORD64) &gGtaThreadNew; //Replace the VMT pointer with a pointer to our new VMT.
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

    return 0; //We no longer need the lpHookScript thread because our Trampoline function will now be the hip and or hop hang out spot for the KewlKidzKlub®.
}

void InjectedScript::Start(HMODULE hInstance) {
    CreateThread(0, 0, lpHookScript, 0, 0, 0);
}

void InjectedScript::Shutdown() {
}