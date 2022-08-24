#include "Log.h"

void Log::Outstr(const std::string& _content) {
	Log::Outstr(_content, DEFAULT_LOGLEVEL);
}
void Log::Outstr(const std::string& _content, LogLevel _level) {
	std::string levelMessage;
	switch (_level) {
	case LogLevel::MESSAGE:
		levelMessage = "[ MESSAGE ]\t";
		break;
	case LogLevel::INFO:
		levelMessage = "[ INFO ]\t";
		break;
	case LogLevel::WARNING:
		levelMessage = "[ WARNING ]\t";
		break;
	case LogLevel::ERROR:
		levelMessage = "[ ERROR ]\t";
		break;
	case LogLevel::ERROR_FATAL:
		levelMessage = "[ ERROR_FATAL ]\t";
		break;
	}

	time_t calendarTime;
	char timeFormatBuffer[256];

	time(&calendarTime);
	tm timeInfo;
	localtime_s(&timeInfo, &calendarTime);
	strftime(timeFormatBuffer, 256, "[%a, %x: %X]\t", &timeInfo);

	std::cout << levelMessage << timeFormatBuffer << "\033[" << _level << "m" << _content << "\033[" << ANSIColorCode::FG_DEFAULT << "m" << std::endl;
}