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

#pragma once

#ifdef DEBUG
#define DEBUGOUT( X, ... ) Logger::Debug( X, __VA_ARGS__ )
#else
#define DEBUGOUT( X, ... )
#endif

#define WRITE(LEVEL, LOGFILE) \
    va_list va_alist; \
    WCHAR chLogBuff[4096]; \
    WCHAR chParameters[3500]; \
    WCHAR szTimestamp[30]; \
    struct tm current_tm; \
    time_t current_time = time(NULL); \
    localtime_s(&current_tm, &current_time); \
    swprintf(szTimestamp, 31, L"[%02d:%02d:%02d] ["#LEVEL"] %%s\n", current_tm.tm_hour, current_tm.tm_min, current_tm.tm_sec); \
    va_start(va_alist, fmt); \
    _vsnwprintf_s(chParameters, sizeof(chParameters), fmt, va_alist); \
    va_end(va_alist); \
    swprintf(chLogBuff, 4096, szTimestamp, chParameters); \
    Write(chLogBuff, LOGFILE);

class Logger {
public:
    static void Init(HMODULE hModule);
    static void Info(const WCHAR* fmt, ...);
    static void Debug(const WCHAR* fmt, ...);
    static void Error(const WCHAR* fmt, ...);
    static void Warn(const WCHAR* fmt, ...);
    static void Fatal(const WCHAR* fmt, ...);
private:
    static void Write(const WCHAR* data, const WCHAR* file);
};