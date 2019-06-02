#pragma once

#include "Craft/Core.h"

namespace Craft
{
	struct Members;

	class CRAFT_API Timer
	{
	private:
		byte m_Reserved[32];
		Members* m_Members;

	public:
		// Creates and starts timer
		Timer();
		~Timer();

		// Resets and restarts timer
		virtual void Reset();
		// Returns time in seconds
		virtual f32 Elapsed();
		// Returns time in milliseconds
		virtual f32 ElapsedMillisecond();
	};
}