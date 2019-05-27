#pragma once

#include "Craft/Types.h"
#include "Event.h"

namespace Craft
{
	
	class CRAFT_API KeyEvent : public Event
	{
	public: 
		inline s32 GetKeyCode() { return m_KeyCode; }
		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

	protected:
		KeyEvent(s32 keyCode) : m_KeyCode(keyCode)
		{
		}

		s32 m_KeyCode;
	};

	class CRAFT_API KeyPressedEvent : public KeyEvent
	{
	public: 
		EVENT_CLASS_TYPE(KeyPressed)

		KeyPressedEvent(s32 keyCode, u32 repeatCount) : 
			KeyEvent(keyCode),
			m_RepeatCount(repeatCount)
		{
		}

		inline u32 GetRpeatCount() { return m_RepeatCount; }

	private:
		u32 m_RepeatCount;
	};

	class CRAFT_API KeyReleasedEvent : public KeyEvent
	{
	public:
		EVENT_CLASS_TYPE(KeyRelease)

		KeyReleasedEvent(s32 keyCode, u32 repeatCount) :
			KeyEvent(keyCode),
			m_RepeatCount(repeatCount)
		{
		}

		inline u32 GetRpeatCount() { return m_RepeatCount; }

	private:
		u32 m_RepeatCount;
	};
}