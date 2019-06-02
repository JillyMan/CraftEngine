#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Craft {

	class CRAFT_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_Core_Logger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_Client_Logger; }

	private:
		static std::shared_ptr<spdlog::logger> s_Core_Logger;
		static std::shared_ptr<spdlog::logger> s_Client_Logger;
	};
}

//Fix name
#ifndef DEBUG_BUILD_DLL

// Core log macros
#define CR_CORE_INFO(...)   ::Craft::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CR_CORE_WARN(...)   ::Craft::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CR_CORE_ERROR(...)  ::Craft::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CR_CORE_TRACE(...)  ::Craft::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CR_CORE_FATAL(...)  ::Craft::Log::GetCoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define CR_INFO(...)		::Craft::Log::GetClientLogger()->info(__VA_ARGS__)
#define CR_WARN(...)		::Craft::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CR_ERROR(...)		::Craft::Log::GetClientLogger()->error(__VA_ARGS__)
#define CR_TRACE(...)		::Craft::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CR_FATAL(...)		::Craft::Log::GetClientLogger()->fatal(__VA_ARGS__)

#else 
// Core log macros
#define CR_CORE_INFO(...)
#define CR_CORE_WARN(...)
#define CR_CORE_ERROR(...)
#define CR_CORE_TRACE(...)
#define CR_CORE_FATAL(...)

// Client log macros
#define CR_INFO(...)
#define CR_WARN(...)
#define CR_ERROR(...)
#define CR_TRACE(...)
#define CR_FATAL(...)
#endif