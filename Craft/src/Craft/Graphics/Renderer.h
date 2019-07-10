#pragma once

#include "Camera.h"
#include "RenderCommand.h"

#include "Primitives\Shape.h"

namespace Craft
{
	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void Submit(Shape& shape);

	private:
		struct SceneData
		{
			mat4 m_ViewProjectionMatrix;
		};

		static SceneData Data;
	};
}