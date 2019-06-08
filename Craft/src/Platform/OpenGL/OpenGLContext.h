#pragma once

#include "Craft\Window\WindowHandle.h"
#include "Craft\Graphics\GraphicsContext.h"

namespace Craft
{
	struct GLInitData
	{
		bool VSync;
		WindowHandle Handle;
	};

	class OpengGLContext : public GraphicsContext
	{
	public:
		OpengGLContext(GLInitData initData);
		~OpengGLContext();

		virtual void Init();
		virtual void SwapBuffers();

	private:
		GLInitData m_InitData;
	};
}