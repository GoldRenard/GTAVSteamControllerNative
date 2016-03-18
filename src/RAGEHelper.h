#pragma once

#include "stdafx.h"

NativeRegistration** GetRegistrationTable();
NativeHandler GetNativeHandler(UINT64 hash);
rage::scrThread* GetActiveThread();
rage::pgPtrCollection<GtaThread>* GetGtaThreadCollection(BlipList*& pBlipList);
void SetActiveThread(rage::scrThread* thread);