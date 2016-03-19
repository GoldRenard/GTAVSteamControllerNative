#include "stdafx.h"

scrThread* GetActiveThread() {
    char* moduleTls = *(char**) __readgsqword(88);
    return *reinterpret_cast<scrThread**>(moduleTls + 2096);
}

void SetActiveThread(scrThread* thread) {
    char* moduleTls = *(char**) __readgsqword(88);
    *reinterpret_cast<scrThread**>(moduleTls + 2096) = thread;
}