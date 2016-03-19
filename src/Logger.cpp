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

char g_logFile[MAX_PATH];
char g_debugLogFile[MAX_PATH];

void Logger::Init(HMODULE hModule) {
    memset(g_logFile, 0, sizeof(g_logFile));

    if (GetModuleFileNameA(hModule, g_logFile, MAX_PATH) != 0) {
        size_t slash = -1;

        for (size_t i = 0; i < strlen(g_logFile); i++) {
            if (g_logFile[i] == '/' || g_logFile[i] == '\\') {
                slash = i;
            }
        }

        if (slash != -1) {
            g_logFile[slash + 1] = '\0';
            strcpy_s(g_debugLogFile, g_logFile);
            strcat_s(g_debugLogFile, "debug.log");
            strcat_s(g_logFile, "hook.log");
        }
        else {
            MessageBoxA(NULL, "Unable to parse target module path", "ERROR", MB_OK);
            ExitProcess(0);
        }
    }
    else {
        MessageBoxA(NULL, "GetModuleFileNameA failed", "ERROR", MB_OK);
        ExitProcess(0);
    }
}

#define WRITE(LEVEL, LOGFILE) \
    va_list va_alist; \
    char chLogBuff[4096]; \
    char chParameters[3500]; \
    char szTimestamp[30]; \
    struct tm current_tm; \
    time_t current_time = time(NULL); \
    FILE* file; \
    localtime_s(&current_tm, &current_time); \
    sprintf_s(szTimestamp, "[%02d:%02d:%02d] ["#LEVEL"] %%s\n", current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec); \
    va_start(va_alist, fmt);  \
    _vsnprintf_s(chParameters, sizeof(chParameters), fmt, va_alist); \
    va_end(va_alist); \
    sprintf_s(chLogBuff, szTimestamp, chParameters); \
    if ((fopen_s(&file, LOGFILE, "a")) == 0) { \
        fprintf_s(file, "%s", chLogBuff); \
        fclose(file); \
    }

void Logger::Info(const char* fmt, ...) {
    WRITE(MSG, g_logFile);
}

void Logger::Debug(const char* fmt, ...) {
    WRITE(DEBUG, g_debugLogFile);
}

void Logger::Error(const char* fmt, ...) {
    WRITE(ERROR, g_debugLogFile);
    MessageBoxA(NULL, chLogBuff, "ERROR", MB_ICONERROR);
}

void Logger::Fatal(const char* fmt, ...) {
    WRITE(FATAL, g_debugLogFile);
    MessageBoxA(NULL, chLogBuff, "FATAL ERROR", MB_ICONERROR);
    ExitProcess(0);
}