#include "stdafx.h"

DWORD64 dwRegistrationTablePtr = 0;
DWORD64 dwThreadCollectionPtr = 0;

NativeRegistration** GetRegistrationTable()
{
	if (!dwRegistrationTablePtr) {
		dwRegistrationTablePtr = Pattern::Scan(g_MainModuleInfo, "76 61 49 8B 7A 40 48 8D 0D");

		if (!dwRegistrationTablePtr) {
			Log::Fatal("Unable to find Native Registration Table");
		}

		dwRegistrationTablePtr += 6;

		DWORD64 dwAddressOfRegistrationTable = dwRegistrationTablePtr + *(DWORD*)(dwRegistrationTablePtr + 3) + 7;

		if (!dwAddressOfRegistrationTable ||
			dwAddressOfRegistrationTable < (DWORD64)g_MainModuleInfo.lpBaseOfDll ||
			dwAddressOfRegistrationTable >(DWORD64) g_MainModuleInfo.lpBaseOfDll + g_MainModuleInfo.SizeOfImage) {
			Log::Fatal("Error reading Native Registration Table opcode (0x%I64X)", dwAddressOfRegistrationTable);
		}

		dwRegistrationTablePtr = dwAddressOfRegistrationTable;
		DEBUGOUT("dwRegistrationTablePtr = 0x%I64X", dwRegistrationTablePtr);
	}

	return (NativeRegistration**)dwRegistrationTablePtr;
}

NativeHandler GetNativeHandler(UINT64 hash)
{
	NativeRegistration** registrationTable = GetRegistrationTable();

	if (!registrationTable)
		return nullptr;

	NativeRegistration* table = registrationTable[hash & 0xFF];

	for (; table; table = table->nextRegistration)
	{
		for (UINT32 i = 0; i < table->numEntries; i++)
		{
			if (hash == table->hashes[i])
			{
				return table->handlers[i];
			}
		}
	}

	return nullptr;
}

void NativeInvoke::Invoke(NativeContext *cxt, UINT64 hash)
{
	auto fn = GetNativeHandler(hash);

	if (fn != 0)
	{
		fn(cxt);
	}
}

rage::pgPtrCollection<GtaThread>* GetGtaThreadCollection(BlipList*& pBlipList)
{
	if (!dwThreadCollectionPtr) {
		dwThreadCollectionPtr = Pattern::Scan(g_MainModuleInfo, "48 8B 05 ? ? ? ? 8B CA 4C 8B 0C C8 45 39 51 08");

		if (!dwThreadCollectionPtr) {
			Log::Fatal("Unable to find GTA Thread Pool");
		}

		DWORD64 dwAddressOfThreadCollection = dwThreadCollectionPtr + *(DWORD*)(dwThreadCollectionPtr + 3) + 7;

		if (!dwAddressOfThreadCollection ||
			dwAddressOfThreadCollection < (DWORD64)g_MainModuleInfo.lpBaseOfDll ||
			dwAddressOfThreadCollection >(DWORD64) g_MainModuleInfo.lpBaseOfDll + g_MainModuleInfo.SizeOfImage) {
			Log::Fatal("Error reading GTA Thread Pool opcode (0x%I64X)", dwAddressOfThreadCollection);
		}

		dwThreadCollectionPtr = dwAddressOfThreadCollection;
		DEBUGOUT("dwThreadCollectionPtr = 0x%I64X", dwThreadCollectionPtr);

		DWORD64 blipCollectionSignature = Pattern::Scan(g_MainModuleInfo, "4C 8D 05 ? ? ? ? 0F B7 C1");

		pBlipList = (BlipList*)(blipCollectionSignature + *(DWORD*)(blipCollectionSignature + 3) + 7);

		DEBUGOUT("pBlipList = 0x%I64X", pBlipList);
	}

	return (rage::pgPtrCollection<GtaThread>*) dwThreadCollectionPtr;
}

//https://s-media-cache-ak0.pinimg.com/236x/a5/32/43/a5324394baa368ef5273ef2e95a2976c.jpg
rage::scrThread* GetActiveThread()
{
	char* moduleTls = *(char**)__readgsqword(88);

	return *reinterpret_cast<rage::scrThread**>(moduleTls + 2096); //citizenMP sigs this offset. It's been the same for 3 versions. Not worth it.
}
//I won't even begin to claim that I know what the fuck is going on here. ~gir489
void SetActiveThread(rage::scrThread* thread)
{
	char* moduleTls = *(char**)__readgsqword(88);

	*reinterpret_cast<rage::scrThread**>(moduleTls + 2096) = thread;
}