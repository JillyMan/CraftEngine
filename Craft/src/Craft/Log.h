#pragma once

#include "Core.h"
#include "Logger\CRLogger.h"

namespace Craft {

	class CRAFT_API Log
	{
	public:
		static void Init();

		inline static crlogger::Logger* GetCoreLogger() { return s_Core_Logger; }
		inline static crlogger::Logger* GetClientLogger() { return s_Client_Logger; }

	private:
		static crlogger::Logger* s_Core_Logger;
		static crlogger::Logger* s_Client_Logger;
	};
}

#ifndef CR_DEBUG

#define CR_CORE_INFO(...)	::Craft::Log::GetCoreLogger()->Info(__VA_ARGS__)
#define CR_CORE_WARN(...)	::Craft::Log::GetCoreLogger()->Warn(__VA_ARGS__)
#define CR_CORE_ERROR(...)	::Craft::Log::GetCoreLogger()->Error(__VA_ARGS__)
#define CR_CORE_TRACE(...)	::Craft::Log::GetCoreLogger()->Trace(__VA_ARGS__)
#define CR_CORE_FATAL(...)	::Craft::Log::GetCoreLogger()->Fatal(__VA_ARGS__)

#define CR_INFO(...)		::Craft::Log::GetClientLogger()->Info(__VA_ARGS__)
#define CR_WARN(...)		::Craft::Log::GetClientLogger()->Warn(__VA_ARGS__)
#define CR_ERROR(...)		::Craft::Log::GetClientLogger()->Error(__VA_ARGS__)
#define CR_TRACE(...)		::Craft::Log::GetClientLogger()->Trace(__VA_ARGS__)
#define CR_FATAL(...)		::Craft::Log::GetClientLogger()->Fatal(__VA_ARGS__)

#else 
#define CR_CORE_INFO(...)
#define CR_CORE_WARN(...)
#define CR_CORE_ERROR(...)
#define CR_CORE_TRACE(...)
#define CR_CORE_FATAL(...)

#define CR_INFO(...)
#define CR_WARN(...)
#define CR_ERROR(...)
#define CR_TRACE(...)
#define CR_FATAL(...)
#endif