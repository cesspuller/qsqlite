#include "TLogger.hpp"

std::shared_ptr<Logger> Logger::loggerInstance;


/**
* Configure Logger Preferences
* @param logFile
* @param level: LogLevel::ERROR by Default
* @param output: LogOutput::CONSOLE by Default
* @return void
*/
void Logger::SetLogPreferences( std::string logFileName = "",
										  LogLevel level = LogLevel::ERROR,
										  LogOutput output = LogOutput::CONSOLE )
{
	logLevel = level;
	logOutput = output;

	if ( logOutput == LogOutput::FILE && !logFileName.empty() )
	{
		logFile.open( logFileName, std::ios::app );

		if ( !logFile.good() )
		{
			std::cerr << "Can't Open Log File" << std::endl;
			logOutput = LogOutput::CONSOLE;
		}
	}
}

/**
* Get Single Logger Instance or Create new Object if Not Created
* @return std::shared_ptr<Logger>
*/
std::shared_ptr<Logger> Logger::GetInstance()
{
	if ( loggerInstance == nullptr )
	{
		loggerInstance = std::shared_ptr<Logger>( new Logger() );
	}

	return loggerInstance;
}

/**
* Log given message with defined parameters and generate message to pass on Console or File
* @param codeFile: __FILE__
* @param codeLine: __LINE__
* @param message: Log Message
* @param messageLevel: Log Level, LogLevel::DEBUG by default
*/
void Logger::Log( int codeLine, std::string message, LogLevel messageLevel = LogLevel::DEBUG )
{
	
		std::string logType;
		//Set Log Level Name
		switch ( messageLevel )
		{
			case LogLevel::DEBUG:
				logType = "DEBUG: ";
				break;
			case LogLevel::INFO:
				logType = "INFO: ";
				break;
			case LogLevel::WARN:
				logType = "WARN: ";
				break;
			case LogLevel::ERROR:
				logType = "ERROR: ";
				break;
			default:
				logType = "NONE: ";
				break;
		}

		message = logType + std::to_string(codeLine) + " " + message;

		LogMessage( message );
}

/**
* Convert String Representation of Log Level to LogLevel Type
* @param logLevel : String log level
* @return LogLevel
*/
LogLevel Logger::GetLogLevel( const std::string& logLevel )
{
	if ( logLevel == "DEBUG" )
	{
		return LogLevel::DEBUG;
	}
	else if ( logLevel == "INFO" )
	{
		return LogLevel::INFO;
	}
	else if ( logLevel == "WARN" )
	{
		return LogLevel::ERROR;
	}
	else if ( logLevel == "ERROR" )
	{
		return LogLevel::ERROR;
	}
	return LogLevel::NONE;
}

/**
* Convert String Representation of Log Output to LogOutput Type
* @param logOutput : String log output
* @return LogOutput
*/
LogOutput Logger::GetLogOutput( const std::string& logOutput )
{
	if ( logOutput == "FILE" )
	{
		return LogOutput::FILE;
	}
	//If corrupted string passed output will be on console
	return LogOutput::CONSOLE;
}

/**
 * Write out the message to target output
 * @param message : String message
 * @return void
 */
void Logger::LogMessage( const std::string& message )
{
	if ( logOutput == LogOutput::FILE )
	{
		logFile << message << std::endl;
	}
	else
	{
		std::cout << message << std::endl;
	}
}