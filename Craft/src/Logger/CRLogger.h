#pragma once

#include <string>

namespace crlogger
{
	static const char* LogNames[] = { "Info", "Fatal", "Warn", "Error", "Trace" };
	static const int Colors[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

	enum ConsoleColor
	{
		GRAY	= 8,
		BLUE	= 9,
		RED		= 12,
		YELLOW	= 14,
		WHITE	= 15
	};

	enum LevelLog
	{
		Info = 0,
		Fatal,
		Warn,
		Error,
		Trace
	};

	class LogStream
	{
	public:
		virtual void Write(LevelLog level, const char* msg) = 0;
	};

	class ConsoleLogStream : public LogStream
	{
	private:
		FILE* m_File;

	public:
		ConsoleLogStream();
		virtual void Write(LevelLog level, const char* msg) override;
	};

	class Logger
	{
	private:
		const char* m_Name;
		LogStream* m_LogStream;

	public:
		Logger(const char* name, LogStream* stream);
		~Logger();

		template<typename... Args>
		void Info(const char* msg, const Args&... args)
		{
			Log(ConsoleColor::WHITE, LevelLog::Info, msg, args...);
		}

		template<typename... Args>
		void Warn(const char* msg, const Args&... args)
		{
			Log(ConsoleColor::BLUE, LevelLog::Warn, msg, args...);
		}

		template<typename... Args>
		void Error(const char* msg, const Args&... args)
		{
			Log(ConsoleColor::RED, LevelLog::Error, msg, args...);
		}

		template<typename... Args>
		void Trace(const char* msg, const Args&... args)
		{
			Log(ConsoleColor::YELLOW, LevelLog::Trace, msg, args...);
		}

		template<typename... Args>
		void Fatal(const char* msg, const Args&... args)
		{
			Log(ConsoleColor::GRAY, LevelLog::Fatal, msg, args...);
		}

		template<typename... Args>
		void Info(std::string& msg, const Args&... args)
		{
			Info(msg.c_str(), args...);
		}

		template<typename... Args>
		void Warn(std::string& msg, const Args&... args)
		{
			Warn(msg.c_str(), args...);
		}

		template<typename... Args>
		void Error(std::string&  msg, const Args&... args)
		{
			Error(msg.c_str(), args...);
		}

		template<typename... Args>
		void Trace(std::string&  msg, const Args&... args)
		{
			Trace(msg.c_str(), args...);
		}

		template<typename... Args>
		void Fatal(std::string& msg, const Args&... args)
		{
			Fatal(msg.c_str(), args...);
		}

		template<typename... Args>
		void Log(ConsoleColor color, LevelLog level, const char* msg, const Args&... args)
		{
			std::stringstream ss;

			char buffer[512];
			sprintf_s(buffer, 512, msg, args...);

			ss << "[" << LogNames[level] << "] " << m_Name << " : " << buffer << "\n";

			m_LogStream->Write(level, ss.str().c_str());
		}
	};

	Logger* CreateConsoleLogger(const char* name);
}