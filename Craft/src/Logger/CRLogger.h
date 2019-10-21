#pragma once

#include <string>
#include <Logger/LogCore.h>
#include <Logger/LogStream.h>

namespace crlogger
{
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
			Log(LevelLog::Info, msg, args...);
		}

		template<typename... Args>
		void Warn(const char* msg, const Args&... args)
		{
			Log(LevelLog::Warn, msg, args...);
		}

		template<typename... Args>
		void Error(const char* msg, const Args&... args)
		{
			Log(LevelLog::Error, msg, args...);
		}

		template<typename... Args>
		void Trace(const char* msg, const Args&... args)
		{
			Log(LevelLog::Trace, msg, args...);
		}

		template<typename... Args>
		void Fatal(const char* msg, const Args&... args)
		{
			Log(LevelLog::Fatal, msg, args...);
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
		void Log(LevelLog level, const char* msg, const Args&... args)
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