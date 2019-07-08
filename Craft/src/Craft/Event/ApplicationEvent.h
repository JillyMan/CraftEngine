#pragma once

#include "crpch.h"
#include "Event.h"

namespace Craft
{
	class CRAFT_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(s32 width, s32 height) :
			m_Width(width), m_Height(height)
		{
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		inline s32 GetWidth() { return m_Width; }
		inline s32 GetHeight() { return m_Height; }

		String ToString() const override
		{
			std::stringstream ss;
			ss << "Window resize: (" << m_Width << ", " << m_Height << ")";
			return ss.str();
		}

	private:
		s32 m_Width, m_Height;
	};

	class CRAFT_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent()
		{
		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		String ToString() const override
		{
			std::stringstream ss;
			ss << "Window close";
			return ss.str();
		}
	};

	class CRAFT_API AppTickEvent : public Event
	{
	public:
		AppTickEvent()
		{
		}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		
		String ToString() const override
		{
			std::stringstream ss;
			ss << "Application tick";
			return ss.str();
		}
	};

	class CRAFT_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent()
		{
		}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
		
		String ToString() const override
		{
			std::stringstream ss;
			ss << "Application render";
			return ss.str();
		}
	};

	class CRAFT_API AppUpdateEvent : public Event
	{
	public:
		AppUpdateEvent()
		{
		}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

		String ToString() const override
		{
			std::stringstream ss;
			ss << "Application update";
			return ss.str();
		}
	};
}