#pragma once

#include "crpch.h"

#include "Event.h"

namespace Craft
{
	class CRAFT_API KeyEvent : public Craft::Event
	{
	public:
		inline s32 GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)
	protected:
		KeyEvent(s32 keycode) : 
			m_KeyCode(keycode) 
		{
		}

		s32 m_KeyCode;
	};

	class CRAFT_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(s32 keycode, u32 repeatCount) : 
			KeyEvent(keycode), 
			m_RepeatCount(repeatCount) 
		{
		}

		inline u32 GetRepeatCount() const { return m_RepeatCount; }

		String ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	private:
		u32 m_RepeatCount;
	};

	class CRAFT_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(s32 keycode) : 
			KeyEvent(keycode) 
		{
		}

		String ToString() const override
		{
			std::stringstream ss;
			ss << "KeyReleasedEvent: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}