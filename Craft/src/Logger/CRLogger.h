#pragma once

#include <stdio.h>
#include <string>

namespace crlogger
{
	static const char* LogNames[] = { "Info", "Fatal", "Warn", "Error", "Trace" };

	enum ConsoleColor
	{
		GRAY	= 8,
		BLUE	= 9,
		RED		= 12,
		YELLOW	= 14,
		WHITE	= 15
	};

	enum class LoggerType
	{
		Console
	};

	enum class LevelLog 
	{
		Info = 0,
		Fatal,
		Warn,
		Error,
		Trace
	};

	class CRAFT_API Logger
	{
	protected:
		const char* m_Name;
		Logger(const char* name) : 
			m_Name(name)
		{
		}

	public:
		template<typename... Args>
		virtual void Info(const char* msg, const Args&... args) = 0;
	
		template<typename... Args>
		virtual void Warn(const char* msg, const Args&... args) = 0;
		
		template<typename... Args>
		virtual void Error(const char* msg, const Args&... args) = 0;
		
		template<typename... Args>
		virtual void Trace(const char* msg, const Args&... args) = 0;
		
		template<typename... Args>
		virtual void Fatal(const char* msg, const Args&... args) = 0;

		static Logger* GetConsoleLogger(const char* name);
	};

	class ConsoleLogger : public Logger
	{
	private:
		FILE* m_File;
	public:

		ConsoleLogger(const char* name, FILE* file) : 
			Logger(name), m_File(file)
		{
		}

		template<typename... Args>
		virtual void Log(LevelLog level, const char* msg, const Args&... args) override
		{
			fprintf(m_File, mgs, args);
		}

		template<typename... Args>
		void Info(const char* msg, const Args&... args) override
		{
			Log(LevelLog::Info, msg, args...);
		}

		template<typename... Args>
		void Warn(const char* msg, const Args&... args) override
		{
			Log(LevelLog::Warn, msg, args...);
		}

		template<typename... Args>
		virtual void Error(const char* msg, const Args&... args) override
		{
			Log(LevelLog::Error, msg, args...);
		}
		
		template<typename... Args>
		virtual void Trace(const char* msg, const Args&... args) override
		{
			Log(LevelLog::Trace, msg, args...);
		}

		template<typename... Args>
		virtual void Fatal(const char* msg, const Args&... args) override
		{
			Log(LevelLog::Fatal, msg, args...);
		}

		template<typename... Args>
		void Log(ConsoleColor color, LevelLog level, const char* msg, const Args&... args)
		{
#ifdef _WIN32
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttrib(hConsole, color);
#endif

			std::stringstream ss;
			ss << "[" << LogNames[level] << "] " << m_Name << " : " << msg << "\n";
			const char* result = ss.str().c_str();			
			fprintf(m_File, result, args);

#ifdef _WIN32
			SetConsoleTextAttrib(hConsole, ConsoleColor::WHITE);
#endif
		}

		static Logger* GetConsoleLogger(const char* name)
		{
			return new ConsoleLogger(name, stdout);
		}
	};
}