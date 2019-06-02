#pragma once

#include "Craft/Core.h"
#include "Craft/Graphics/Window/Window.h"

namespace Craft { namespace Graphics {

	enum class CRAFT_API RenderApi
	{
		None,
		Own,
		OpenGL,
		DirectX
	};

	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;
	};
} }