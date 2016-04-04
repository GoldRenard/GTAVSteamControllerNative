#include "stdafx.h"
#include "resource.h"
#include "InjectedScript.h"

InjectedScript *InjectedScript::m_Instance = NULL;

const std::wstring GetLibraryPath(const WCHAR* libraryName) {
    std::wstring strTempPath;
    wchar_t wchPath[MAX_PATH];
    if (GetTempPathW(MAX_PATH, wchPath)) {
        strTempPath = wchPath;
        if (strTempPath[strTempPath.size() - 1] != L'\\') {
            strTempPath += L'\\';
        }
        strTempPath.append(libraryName);
        return strTempPath;
    }
    return NULL;
}

bool ExtractResource(const HINSTANCE hInstance, WORD resourceID, const WCHAR* szFilename) {
    try {
        // Find and load the resource
        HRSRC hResource = FindResource(hInstance, MAKEINTRESOURCE(resourceID), L"BINARY");
        if (!hResource) {
            return false;
        }
        HGLOBAL hFileResource = LoadResource(hInstance, hResource);

        // Open and map this to a disk file
        LPVOID lpFile = LockResource(hFileResource);
        DWORD dwSize = SizeofResource(hInstance, hResource);

        // Open the file and filemap
        HANDLE hFile = CreateFile(szFilename, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
        HANDLE hFileMap = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, dwSize, NULL);
        LPVOID lpAddress = MapViewOfFile(hFileMap, FILE_MAP_WRITE, 0, 0, 0);

        // Write the file
        CopyMemory(lpAddress, lpFile, dwSize);

        // Un-map the file and close the handles
        UnmapViewOfFile(lpAddress);
        CloseHandle(hFileMap);
        CloseHandle(hFile);
        return true;
    }
    catch (...) {
        return false;
    }
}

void InjectedScript::Start(HMODULE hInstance) {
    std::wstring mLibraryPath = GetLibraryPath(STEAM_API_DLL);
    if (!ExtractResource(hInstance, IDR_BINARY1, mLibraryPath.c_str())) {
        Logger::Fatal(L"Could not extract original library to %s", mLibraryPath.c_str());
        return;
    }
    SteamAPI_InitProxy(mLibraryPath.c_str());
}

void InjectedScript::Shutdown() {
    SteamAPI_CloseProxy();
}