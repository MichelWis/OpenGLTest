#pragma once
#define DEFAULT_LOGLEVEL LogLevel::INFO
#include <iostream>
#include <string>
#include <ctime>
#include "Printable.h"

enum ANSIColorCode {
	FG_RED = 31,
	FG_GREEN = 32,
	FG_YELLOW = 33,
	FG_BLUE = 34,
	FG_MAGENTA = 35,
	FG_DEFAULT = 39
};

enum LogLevel
{
	//MESSAGE, INFO, WARNING, ERROR, ERROR_FATAL
	MESSAGE = ANSIColorCode::FG_GREEN, INFO = ANSIColorCode::FG_BLUE, WARNING = ANSIColorCode::FG_YELLOW, ERROR = ANSIColorCode::FG_RED, ERROR_FATAL = ANSIColorCode::FG_MAGENTA
};

static class Log {
public:
	template<typename ...Args>
	static void Out(Args const&... _objectsToLog)
	{
		std::string resultString = "";
		r_Out(resultString, _objectsToLog...);
		Outstr(resultString);
	}
	template<typename ...Args>
	static void Out(LogLevel _logLevel, Args const&... _objectsToLog)
	{
		std::string resultString = "";
		r_Out(resultString, _objectsToLog...);
		Outstr(resultString, _logLevel);
	}

private:
	template<typename Arg, typename ...Args>
	static void r_Out(std::string& _resultString, const Arg &_firstObjectToPrint, const Args &..._objectsToPrint)
	{
		// extract first argument and then...		
		Printable<Arg> tmp (_firstObjectToPrint);
		_resultString.append(tmp.GetString());
		// ...expand until the expansion evaluates to a single argument
		r_Out(_resultString, _objectsToPrint...);
	}
	// base case of recursive call
	template<typename Arg>
	static void r_Out(std::string &_resultString, const Arg& _objectToPrint) 
	{
		Printable<Arg> tmp = _objectToPrint;
		_resultString.append(tmp.GetString());
	}

	template<typename ...Args>
	static void r_Out(std::string& _resultString, const char _firstObjectToPrint[], Args const&..._objectsToPrint)
	{		
		// extract first argument and then...		
		Printable<const char*> tmp((const char*)_firstObjectToPrint);
		_resultString.append(tmp.GetString());
		// ...expand until the expansion evaluates to a single argument
		r_Out(_resultString, _objectsToPrint...);
	}
	// base case of recursive call
	static void r_Out(std::string& _resultString, const char _objectToPrint[])
	{
		Printable<const char*> tmp = (const char*)_objectToPrint;
		_resultString.append(tmp.GetString());
	}

	static void Outstr(const std::string& message);
	static void Outstr(const std::string& message, LogLevel _overrideLogLevel);
};