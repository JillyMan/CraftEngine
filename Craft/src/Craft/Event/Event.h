#pragma once

#include <functional>
#include "Craft/Core.h"

namespace Craft
{
	//<enum class> vs <enum>
	enum class EventType
	{
		None = 0,
		AppTick, AppRender, AppUpdate,
		MouseMoved, MouseButtonReleased, MouseButtonPressed, MouseScrolled,
		KeyPressed, KeyReleased,
		WindowResize, WindowClose, WindowMoved, WindowFocus, WindowLostFocus
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput		 = BIT(1),
		EventCategoryKeyboard	 = BIT(2),
		EventCategoryMouse		 = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() override { return GetStaticType(); }\
								virtual const char* GetName() override { return #type; }

#define EVENT_CLASS_CATEGORY(category) inline virtual int GetCategoryFlags() override { return category; }

	class CRAFT_API Event
	{
	private:
		friend class EventDispatcher;

	public:
		virtual EventType GetEventType() = 0;
		virtual const char* GetName() = 0;
		virtual int GetCategoryFlags() = 0;
		virtual String ToString() { return GetName(); }
		
		inline bool InCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	protected:
		bool m_Handled = false;
	};

	class EventDispatcher
	{
	private:
		template<typename T>
		using EventFn = std::function<bool(T&)>&;
	
		Event& m_Event;

	public:
		EventDispatcher(Event& event) : 
			m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (T::GetStaticType() == m_Event.GetEventType())
			{
				m_Event.m_Handled = func(*(T*)&m_Event);
				return true;
			}

			return false;
		}
	};

	inline std::ostream& operator<< (std::ostream& os, Event& e)
	{
		return os << e.ToString();
	}
}