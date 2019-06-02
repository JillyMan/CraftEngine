#pragma once

#include "Craft\Core.h"
#include "Craft\Event\Event.h"

namespace Craft
{
	class CRAFT_API Layer
	{
		bool m_Visible;

	public:
		inline bool IsVisible() { return m_Visible; }
		void SetVisible(bool visible) { m_Visible = visible; }

		virtual void OnEvent(Event& event) = 0;
		virtual void OnUpdate(f32 deltaTime) = 0;
		virtual void OnRender() = 0;
	};
}