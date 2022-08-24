#include "ScopeTimer.h"

ScopeTimer::ScopeTimer(std::chrono::duration<double>& _durationOutput)
	: m_duration(_durationOutput)   
{
	m_InitialTime = std::chrono::high_resolution_clock::now();
}

ScopeTimer::~ScopeTimer()
{
	auto endTime = std::chrono::high_resolution_clock::now();
	m_duration = endTime - m_InitialTime;
}

ScopeTimerLogger::ScopeTimerLogger()
{
	m_InitialTime = std::chrono::high_resolution_clock::now();
}

ScopeTimerLogger::ScopeTimerLogger(const char* _logString)
	: m_LogString(_logString)
{
	m_InitialTime = std::chrono::high_resolution_clock::now();
}

ScopeTimerLogger::~ScopeTimerLogger()
{
	auto endTime = std::chrono::high_resolution_clock::now();
	auto dur = std::chrono::duration_cast<std::chrono::microseconds, long long>(endTime - m_InitialTime);
	Log::Out(m_LogString, "[", dur.count() / 1000.f, "ms]");
}