#pragma once

#include "Craft\Core\Core.h"
#include "Craft\Event\Event.h"

namespace Craft
{
	class CRAFT_API Layer
	{
		bool m_Visible;

	public:
		inline bool IsVisible() { return m_Visible; }
		void SetVisible(bool visible) { m_Visible = visible; }

		virtual void OnAttach() {}
		virtual void OnDetach() {}

		virtual void OnEvent(Event& event) {}
		virtual void OnUpdate(f32 deltaTime) {}
		virtual void OnRender() {}
		virtual void OnDebugRender() {};
	};
}