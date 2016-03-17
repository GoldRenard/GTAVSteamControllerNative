#pragma once

#ifdef DEBUG
#define DEBUGOUT( X, ... ) Log::Debug( X, __VA_ARGS__ )
#else
#define DEBUGOUT( X, ... )
#endif

class Log {
public:
	static void Init(HMODULE hModule);
	static void Debug(const char* fmt, ...);
	static void Msg(const char* fmt, ...);
	static void Error(const char* fmt, ...);
	static void Fatal(const char* fmt, ...);
};