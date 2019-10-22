#pragma once

#include "crpch.h"
#include "Event.h"

namespace Craft
{
	class CRAFT_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(s32 xOffset, s32 yOffset) :
			m_XOffset(xOffset), m_YOffset(yOffset)
		{
		}

		inline s32 GetXOffset() { return m_XOffset; }
		inline s32 GetYOffset() { return m_YOffset; }

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		String ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse srcolled: (" << m_XOffset << ", " << m_YOffset << ")";
			return ss.str();
		}

	private:
		s32 m_XOffset, m_YOffset;
	};

	class CRAFT_API MouseScrollWheelEvent : public Event
	{
	public:
		MouseScrollWheelEvent(s32 zDelta) :
			m_ZDelta(zDelta)
		{
		}

		inline s32 GetZDelta() { return m_ZDelta; }

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		String ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse scrol wheel: (" << m_ZDelta << ")";
			return ss.str();
		}

	private:
		s32 m_ZDelta;
	};

	class CRAFT_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(s32 x, s32 y) :
			x(x), y(y)
		{
		}
		
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse)

		String ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse button moved: (" << x << ", " << y << ")";
			return ss.str();
		}

		s32 x, y;
	};


	class CRAFT_API MouseButtonEvent : public Event
	{
	public:
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

		inline s32 GetMouseButton() { return m_Button; }

	protected: 
		MouseButtonEvent(s32 button) : 
			m_Button(button)
		{
		}

	protected:
		s32 m_Button;
	};

	class CRAFT_API MouseButtonPressedEvent : public MouseButtonEvent 
	{
	public:
		
		MouseButtonPressedEvent(s32 button) :
			MouseButtonEvent(button)
		{
		}

		String ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse button pressed: " << m_Button;
			return ss.str();
		}
	
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class CRAFT_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(s32 button) :
			MouseButtonEvent(button)
		{
		}

		String ToString() const override
		{
			std::stringstream ss;
			ss << "Mouse button released: " << m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseButtonReleased)
	};
}