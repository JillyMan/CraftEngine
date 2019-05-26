#pragma once
#include "Core.h"

namespace Craft {

	class CRAFT_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();
}