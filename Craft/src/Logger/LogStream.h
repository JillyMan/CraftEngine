#pragma once

#include <Logger/LogCore.h>
#include <Logger/CRLogger.h>

namespace crlogger 
{
	class LogStream
	{
	public:
		virtual void Write(LevelLog level, const char* msg) = 0;
	};

}