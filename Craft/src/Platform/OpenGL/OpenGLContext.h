#pragma once

#include <Craft\Window\WindowHandle.h>
#include <Craft\Graphics\GraphicsContext.h>

namespace Craft { namespace Graphics {

	struct GLInitData
	{
		bool VSync;
		bool DebugMode;
		WindowHandle Handle;
	};

	class OpengGLContext : public GraphicsContext
	{
	public:
		OpengGLContext(GLInitData initData);
		~OpengGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;
		virtual void VSync(bool enabled) override;

	private:
		GLInitData m_InitData;
	};
}}