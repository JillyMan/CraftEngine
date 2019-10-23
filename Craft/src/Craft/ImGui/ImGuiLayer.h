#pragma once

#include "Craft/Layer.h"

namespace Craft {

	class ImGuiLayer : public Layer 
	{
	public:

		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;

		virtual void OnEvent(Event& event) override;
		virtual void OnUpdate(f32 deltaTime) override;
		virtual void OnRender() override;
	};

}