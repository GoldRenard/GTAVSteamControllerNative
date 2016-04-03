// ======================================================================
// STEAM CONTROLLER NATIVE FOR GRAND THEFT AUTO V
// Copyright (C) 2016 Ilya Egorov (goldrenard@gmail.com)

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.
// ======================================================================

#include "stdafx.h"
#include "Logger.h"
#include <time.h>
#include <stdio.h>

WCHAR g_logFile[MAX_PATH];
WCHAR g_debugLogFile[MAX_PATH];

void Logger::Init(HMODULE hModule) {
    memset(g_logFile, 0, sizeof(g_logFile));

    if (GetModuleFileName(hModule, g_logFile, MAX_PATH) != 0) {
        size_t slash = -1;

        for (size_t i = 0; i < wcslen(g_logFile); i++) {
            if (g_logFile[i] == '/' || g_logFile[i] == '\\') {
                slash = i;
            }
        }

        if (slash != -1) {
            g_logFile[slash + 1] = '\0';
            wcscpy_s(g_debugLogFile, g_logFile);
            wcscpy_s(g_debugLogFile, L"debug.log");
            wcscpy_s(g_logFile, L"hook.log");
        }
        else {
            MessageBox(NULL, L"Unable to parse target module path", L"ERROR", MB_OK);
            ExitProcess(0);
        }
    }
    else {
        MessageBox(NULL, L"GetModuleFileNameA failed", L"ERROR", MB_OK);
        ExitProcess(0);
    }
}

void Logger::Write(const WCHAR* data, const WCHAR* filename) {
    FILE* file;
    if ((_wfopen_s(&file, filename, L"a")) == 0) {
        fwprintf_s(file, L"%s", data);
        fclose(file);
    }
}

void Logger::Info(const WCHAR* fmt, ...) {
    WRITE(MSG, g_logFile);
}

void Logger::Debug(const WCHAR* fmt, ...) {
    WRITE(DEBUG, g_debugLogFile);
}

void Logger::Error(const WCHAR* fmt, ...) {
    WRITE(ERROR, g_debugLogFile);
    MessageBox(NULL, chLogBuff, L"ERROR", MB_ICONERROR);
}

void Logger::Fatal(const WCHAR* fmt, ...) {
    WRITE(FATAL, g_debugLogFile);
    MessageBox(NULL, chLogBuff, L"FATAL ERROR", MB_ICONERROR);
    ExitProcess(0);
}