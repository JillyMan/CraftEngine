#include "crpch.h"

#include <Logger/CRLogger.h>
#include <Logger/ConsoleLogStream.h>

namespace crlogger
{

	Logger::Logger(const char* name, LogStream* stream) :
			m_Name(name), m_LogStream(stream)
	{
	}

	Logger::~Logger()
	{
		delete m_LogStream;
	}

	Logger* CreateConsoleLogger(const char* name)
	{
		return new Logger(name, new ConsoleLogStream());
	}
}