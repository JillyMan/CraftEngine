#pragma once

#include "RenderCommand.h"
#include "OrthographicsCamera.h"

#include "Primitives\Shape.h"

namespace Craft
{
	class Renderer
	{
	public:

		static void BeginScene(OrthographicsCamera& camera);
		static void Submit(Shape& shape);

	private:
		struct SceneData
		{
			mat4 m_ViewProjectionMatrix;
		};

		static SceneData Data;
	};
}