#include "stdafx.h"
#include "NativeInvoker.h"

DWORD64 dwRegistrationTablePtr = 0;
DWORD64 dwThreadCollectionPtr = 0;

NativeRegistration** GetRegistrationTable() {
    if (!dwRegistrationTablePtr) {
        dwRegistrationTablePtr = Pattern::Scan(g_MainModuleInfo, "76 61 49 8B 7A 40 48 8D 0D");

        if (!dwRegistrationTablePtr) {
            DEBUGOUT(L"Unable to find Native Registration Table");
            return nullptr;
        }

        dwRegistrationTablePtr += 6;

        DWORD64 dwAddressOfRegistrationTable = dwRegistrationTablePtr + *(DWORD*) (dwRegistrationTablePtr + 3) + 7;

        if (!dwAddressOfRegistrationTable ||
            dwAddressOfRegistrationTable < (DWORD64) g_MainModuleInfo.lpBaseOfDll ||
            dwAddressOfRegistrationTable >(DWORD64) g_MainModuleInfo.lpBaseOfDll + g_MainModuleInfo.SizeOfImage) {
            Logger::Fatal(L"Error reading Native Registration Table opcode (0x%I64X)", dwAddressOfRegistrationTable);
        }

        dwRegistrationTablePtr = dwAddressOfRegistrationTable;
        DEBUGOUT(L"dwRegistrationTablePtr = 0x%I64X", dwRegistrationTablePtr);
    }

    return (NativeRegistration**) dwRegistrationTablePtr;
}

NativeHandler GetNativeHandler(UINT64 hash) {
    NativeRegistration** registrationTable = GetRegistrationTable();

    if (!registrationTable)
        return nullptr;

    NativeRegistration* table = registrationTable[hash & 0xFF];

    for (; table; table = table->nextRegistration) {
        for (UINT32 i = 0; i < table->numEntries; i++) {
            if (hash == table->hashes[i]) {
                return table->handlers[i];
            }
        }
    }

    return nullptr;
}

void NativeInvoke::Invoke(NativeContext *cxt, UINT64 hash) {
    auto fn = GetNativeHandler(hash);
    if (fn) {
        fn(cxt);
    }
    else {
        DEBUGOUT(L"No native handler found for hash 0x%I64X", hash);
    }
}