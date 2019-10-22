#pragma once

#include <Logger/LogStream.h>

namespace crlogger {

	enum ConsoleColor
	{
		GRAY = 8,
		BLUE = 9,
		RED = 12,
		YELLOW = 14,
		WHITE = 15
	};

	class ConsoleLogStream : public LogStream
	{
	private:
		FILE* m_File;
		std::map<LevelLog, ConsoleColor> m_LogColors;

	public:
		ConsoleLogStream();
		virtual void Write(LevelLog level, const char* msg) override;
	};
}