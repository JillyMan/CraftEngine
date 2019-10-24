#pragma once

#include "Craft/Core/Layer.h"

namespace Craft {

	class CRAFT_API ImGuiLayer : public Layer
	{
	public:

		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnDebugRender() override;

		void Begin();
		void End();

	private:
		f32 m_Time;
	};

}