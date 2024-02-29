#ifndef _T_LOGGER_HPP_
#define _T_LOGGER_HPP_

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

enum class LogLevel
{
	NONE = 0,
	ERROR = 1,
	WARN = 2,
	INFO = 3,
	DEBUG = 4
};

enum class LogOutput
{
	CONSOLE,
	FILE
};


class Logger
{
	public:

	static std::shared_ptr<Logger> GetInstance();

	void SetLogPreferences( std::string logFileName,
									LogLevel level,
									LogOutput output );

	void Log( int codeLine, std::string message, LogLevel messageLevel );

	LogOutput GetLogOutput( const std::string& logOutput );
	LogLevel GetLogLevel( const std::string& logLevel );

	private:
	LogLevel logLevel;
	LogOutput logOutput;
	std::ofstream logFile;

	static std::shared_ptr<Logger> loggerInstance;

	void LogMessage( const std::string& message );
	private:

};


#endif // !_T_LOGGER_HPP_
