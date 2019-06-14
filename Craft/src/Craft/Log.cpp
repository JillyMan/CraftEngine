#include "crpch.h"

#include "Log.h"

namespace Craft {

	crlogger::Logger* Log::s_Core_Logger = nullptr;
	crlogger::Logger* Log::s_Client_Logger = nullptr;

	void Log::Init()
	{
		s_Core_Logger = crlogger::CreateConsoleLogger("CRAFT");
		s_Client_Logger = crlogger::CreateConsoleLogger("APP");
	}
}