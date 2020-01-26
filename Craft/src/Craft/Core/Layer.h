#pragma once

#include "Craft\Core\Core.h"
#include "Craft\Event\Event.h"

namespace Craft
{
	class EventListener {
	public:
		virtual void OnEvent(Event& event) = 0;
	};

	class UpdateListener {
	public:
		virtual void OnUpdate(f32 dt) = 0;
	};

	class CRAFT_API Layer : public EventListener, public UpdateListener
	{
		bool m_Visible;

	public:
		inline bool IsVisible() { return m_Visible; }
		void SetVisible(bool visible) { m_Visible = visible; }

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnEvent(Event& event) override {}
		virtual void OnUpdate(f32 deltaTime) {}
		virtual void OnRender() {}
		virtual void OnDebugRender() {};
	};
}