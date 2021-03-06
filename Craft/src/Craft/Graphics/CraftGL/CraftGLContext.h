#pragma once

#include "Craft\Window\WindowHandle.h"
#include "Craft\Graphics\GraphicsContext.h"

namespace Craft {
	
	using namespace Craft::Graphics;
	class CraftGLContext : public GraphicsContext
	{
	public:
		CraftGLContext(WindowHandle windowHanle);
		~CraftGLContext();

		void Init() override;
		void SwapBuffers() override;

	private:
		WindowHandle m_WindowHandle;
	};
}