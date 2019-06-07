#pragma once

#include "Craft\Window\WindowHandle.h"
#include "Craft\Graphics\GraphicsContext.h"

namespace Craft
{
	class OpengGLContext : public GraphicsContext
	{
	public:
		OpengGLContext(WindowHandle handle);

		virtual void Init();
		virtual void SwapBuffers();


	private:
		WindowHandle m_WindowHandle;
	};
}