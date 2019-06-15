#include "crpch.h"
#include "CRLogger.h"

namespace crlogger
{
	ConsoleLogStream::ConsoleLogStream() :
		m_File(stdout)
	{
		m_LogColors[LevelLog::Error] = ConsoleColor::RED;
		m_LogColors[LevelLog::Fatal] = ConsoleColor::GRAY;
		m_LogColors[LevelLog::Info] = ConsoleColor::WHITE;
		m_LogColors[LevelLog::Trace] = ConsoleColor::GRAY;
		m_LogColors[LevelLog::Warn] = ConsoleColor::YELLOW;
	}

	void ConsoleLogStream::Write(LevelLog level, const char* msg)
	{
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, m_LogColors[level]);
			fprintf(m_File, msg);
			SetConsoleTextAttribute(hConsole, ConsoleColor::WHITE);
	}

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