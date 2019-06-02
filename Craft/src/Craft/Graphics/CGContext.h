#pragma once

#include "GraphicsContext.h"

namespace Craft { namespace Graphics {
	
	// craft graphics
	class CRAFT_API CGContext : public GraphicsContext
	{
	public:
		CGContext();
		~CGContext();

		void Init() override;
		void SwapBuffers() override;
	};
}}