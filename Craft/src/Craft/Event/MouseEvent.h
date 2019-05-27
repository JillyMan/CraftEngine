#pragma once

#include "Craft\Types.h"
#include "Event.h"

namespace Craft
{
	class CRAFT_API MouseButtonPressedEvent : public Event
	{
	public:
		MouseButtonPressedEvent(u32 x, u32 y) :
			x(x), y(y)
		{
		}

		u32 x, y;			
	};

	class CRAFT_API MouseButtonReleasedEvent : public Event
	{
	public:
		MouseButtonReleasedEvent(u32 x, u32 y) :
			x(x), y(y)			
		{
		}

		u32 x, y;
	};

	class CRAFT_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(u32 x, u32 y) :
			x(x), y(y)
		{
		}

		u32 x, y;
	};
}