#pragma once
#include <chrono>
#include <../Logging/Log.h>

#ifdef DEBUG
#define LOG_TIME_SCOPE(outString) ScopeTimerLogger timer##__LINE__(__FUNCSIG__##" took: ");
#else
#define LOG_TIME_SCOPE(outString)
#endif // DEBUG


struct ScopeTimer {
	ScopeTimer(std::chrono::duration<double>& _durationOutput);
	~ScopeTimer();
private:
	std::chrono::high_resolution_clock::time_point m_InitialTime;
	std::chrono::duration<double>& m_duration;
};

struct ScopeTimerLogger {
	ScopeTimerLogger();
	ScopeTimerLogger(const char* _logString);
	~ScopeTimerLogger();
private:
	std::chrono::high_resolution_clock::time_point m_InitialTime;
	std::string m_LogString;
};