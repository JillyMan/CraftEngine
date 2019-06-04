#pragma once

#include "GraphicsContext.h"
#include "Craft\Window\WindowHandle.h"

namespace Craft { namespace Graphics {
	
	class CGContext : public GraphicsContext
	{
	public:
		CGContext(WindowHandle windowHanle);
		~CGContext();

		void Init() override;
		void SwapBuffers() override;

	private:
		WindowHandle m_WindowHandle;
	};
}}