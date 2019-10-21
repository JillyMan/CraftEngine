#pragma once

namespace crlogger 
{
	static const char* LogNames[] = { "Info", "Fatal", "Warn", "Error", "Trace" };

	enum LevelLog
	{
		Info = 0,
		Fatal,
		Warn,
		Error,
		Trace
	};

}