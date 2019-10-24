#pragma once

#include "Craft/Core/Core.h"

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

		
		virtual void Reset();
		virtual f32 Elapsed();
		virtual f32 ElapsedMillisecond();
	};
}